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
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    }

    return ch != EOF || !ferror(stdin);
}

static int read_token(char **buffer)
{
    size_t length = 0;
    size_t capacity = 32;
    int ch;
    char *token;

    if (buffer == NULL) {
        return 0;
    }

    *buffer = NULL;
    token = malloc(capacity);

    if (token == NULL) {
        return 0;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        free(token);
        return 0;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length == SIZE_MAX - 1) {
            free(token);
            discard_token_tail(ch);
            return 0;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(token);
                discard_token_tail(ch);
                return 0;
            }

            new_capacity = capacity * 2;
            resized = realloc(token, new_capacity);

            if (resized == NULL) {
                free(token);
                discard_token_tail(ch);
                return 0;
            }

            token = resized;
            capacity = new_capacity;
        }

        token[length++] = (char)ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    }

    if (ch == EOF && ferror(stdin)) {
        free(token);
        return 0;
    }

    token[length] = '\0';
    *buffer = token;
    return 1;
}

static int read_size(size_t *value)
{
    char *buffer;
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(&buffer)) {
        return 0;
    }

    if (buffer[0] == '\0' || buffer[0] == '+' || buffer[0] == '-') {
        free(buffer);
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        free(buffer);
        return 0;
    }

    *value = (size_t)parsed;
    free(buffer);
    return 1;
}

static int read_int64(int64_t *value)
{
    char *buffer;
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_token(&buffer)) {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < (intmax_t)INT64_MIN || parsed > (intmax_t)INT64_MAX) {
        free(buffer);
        return 0;
    }

    *value = (int64_t)parsed;
    free(buffer);
    return 1;
}

static int max_sum_no_three_consecutive_stream(size_t count, int64_t *result)
{
    int64_t skip = 0;
    int64_t take_one = 0;
    int64_t take_two = 0;
    int have_take_one = 0;
    int have_take_two = 0;
    size_t i;

    if (result == NULL) {
        return 0;
    }

    for (i = 0; i < count; ++i) {
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