#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <ctype.h>

static int read_token(char *buffer, size_t size)
{
    int ch;
    size_t length = 0;
    int too_long = 0;

    if (buffer == NULL || size == 0) {
        return -1;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
        if (ch == EOF) {
            return ferror(stdin) ? -1 : 0;
        }
    } while (isspace((unsigned char)ch));

    do {
        if (!too_long) {
            if (length < size - 1) {
                buffer[length++] = (char)ch;
            } else {
                too_long = 1;
            }
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != EOF && !isspace((unsigned char)ch));

    buffer[length] = '\0';

    if (ch == EOF && ferror(stdin)) {
        return -1;
    }

    return too_long ? -1 : 1;
}

static int read_size(size_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[SIZE_MAX > UINT64_MAX ? 32 : 24];
    char *end = NULL;
    uintmax_t parsed;
    int status;

    if (value == NULL) {
        return 0;
    }

    status = read_token(token, sizeof(token));
    if (status != 1 || token[0] == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_int64(int64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[24];
    char *end = NULL;
    intmax_t parsed;
    int status;

    if (value == NULL) {
        return 0;
    }

    status = read_token(token, sizeof(token));
    if (status != 1) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static int add_int64(int64_t left, int64_t right, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if ((right > 0 && left > INT64_MAX - right) ||
        (right < 0 && left < INT64_MIN - right)) {
        return 0;
    }

    *result = left + right;
    return 1;
}

static size_t max_subsequence_length(const int64_t *array, size_t length,
                                     int64_t difference)
{
    size_t best = 0;

    if (array == NULL || length == 0) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        size_t current = 1;
        int64_t value = array[i];

        for (size_t j = i + 1; j < length; ++j) {
            int64_t next;

            if (!add_int64(value, difference, &next)) {
                break;
            }

            if (array[j] == next) {
                value = next;
                ++current;
            }
        }

        if (current > best) {
            best = current;
        }
    }

    return best;
}

int main(void)
{
    size_t length;
    int64_t difference;
    int64_t *array;

    if (!read_size(&length) || !read_int64(&difference)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == 0) {
        puts("0");
        return EXIT_SUCCESS;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        fputs("Input size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_int64(&array[i])) {
            fputs("Invalid input\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    printf("%zu\n", max_subsequence_length(array, length, difference));

    free(array);
    return EXIT_SUCCESS;
}