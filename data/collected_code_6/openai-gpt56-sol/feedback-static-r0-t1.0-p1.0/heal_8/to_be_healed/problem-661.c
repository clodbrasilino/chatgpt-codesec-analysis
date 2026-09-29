#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>

static int add_checked(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int discard_token_tail(int ch)
{
    while (ch != EOF && !isspace((unsigned char)ch)) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    return ch != EOF || !ferror(stdin);
}

static int read_token(char *buffer, size_t capacity)
{
    size_t length = 0;
    int ch;

    if (buffer == NULL || capacity < 2) {
        return 0;
    }

    buffer[0] = '\0';

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return 0;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length + 1 >= capacity) {
            (void)discard_token_tail(ch);
            buffer[0] = '\0';
            return 0;
        }

        buffer[length++] = (char)ch;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    if (ch == EOF && ferror(stdin)) {
        buffer[0] = '\0';
        return 0;
    }

    buffer[length] = '\0';
    return 1;
}

static int read_size(size_t *value)
{
    enum { BUFFER_SIZE = sizeof(uintmax_t) * CHAR_BIT + 2 };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    char *end = NULL;
    uintmax_t parsed;

    if (value == NULL || !read_token(buffer, sizeof(buffer))) {
        return 0;
    }

    if (buffer[0] == '\0' || buffer[0] == '+' || buffer[0] == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_int64(int64_t *value)
{
    enum { BUFFER_SIZE = sizeof(intmax_t) * CHAR_BIT + 3 };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    char *end = NULL;
    intmax_t parsed;

    if (value == NULL || !read_token(buffer, sizeof(buffer))) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < (intmax_t)INT64_MIN || parsed > (intmax_t)INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static int max_sum_no_three_consecutive_stream(size_t count, int64_t *result)
{
    int64_t skip = 0;
    int64_t take_one = 0;
    int64_t take_two = 0;
    int have_take_one = 0;
    int have_take_two = 0;

    if (result == NULL) {
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        int64_t value;
        int64_t next_skip = skip;
        int64_t next_take_one;
        int64_t next_take_two = 0;
        int next_have_take_two = 0;

        if (!read_int64(&value)) {
            fprintf(stderr, "Failed to read element %zu.\n", i);
            return 0;
        }

        if (have_take_one && take_one > next_skip) {
            next_skip = take_one;
        }

        if (have_take_two && take_two > next_skip) {
            next_skip = take_two;
        }

        if (!add_checked(skip, value, &next_take_one)) {
            return 0;
        }

        if (have_take_one) {
            if (!add_checked(take_one, value, &next_take_two)) {
                return 0;
            }
            next_have_take_two = 1;
        }

        skip = next_skip;
        take_one = next_take_one;
        take_two = next_take_two;
        have_take_one = 1;
        have_take_two = next_have_take_two;
    }

    *result = skip;

    if (have_take_one && take_one > *result) {
        *result = take_one;
    }

    if (have_take_two && take_two > *result) {
        *result = take_two;
    }

    return 1;
}

int main(void)
{
    size_t count;
    int64_t result;

    if (!read_size(&count)) {
        fputs("Failed to read the element count.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!max_sum_no_three_consecutive_stream(count, &result)) {
        fputs("Unable to read input or compute the result safely.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        fputs("Failed to write the result.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}