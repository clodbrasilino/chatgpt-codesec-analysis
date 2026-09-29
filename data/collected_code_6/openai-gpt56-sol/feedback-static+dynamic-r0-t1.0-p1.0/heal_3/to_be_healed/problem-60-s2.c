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

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        if (ch == EOF) {
            return 0;
        }
    } while (isspace((unsigned char)ch));

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length + 1 >= size) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = getchar();
            } while (ch != EOF && !isspace((unsigned char)ch));
            return -1;
        }

        buffer[length++] = (char)ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    }

    buffer[length] = '\0';
    return 1;
}

static int read_size(size_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[64];
    char *end;
    uintmax_t parsed;
    int status = read_token(token, sizeof(token));

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
    char token[64];
    char *end;
    intmax_t parsed;
    int status = read_token(token, sizeof(token));

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

            if ((difference > 0 && value > INT64_MAX - difference) ||
                (difference < 0 && value < INT64_MIN - difference)) {
                continue;
            }

            next = value + difference;

            if (array[j] == next) {
                value = array[j];
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