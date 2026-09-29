#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <limits.h>

static int parse_size(const char *text, size_t *value)
{
    char *end;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' || parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int parse_i64(const char *text, int64_t *value)
{
    char *end;
    intmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static int read_token(char *buffer, size_t size)
{
    int ch;
    size_t length = 0;
    int truncated = 0;

    if (buffer == NULL || size < 2) {
        return 0;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != EOF && (ch == ' ' || ch == '\t' || ch == '\n' ||
                           ch == '\r' || ch == '\f' || ch == '\v'));

    if (ch == EOF) {
        return 0;
    }

    do {
        if (length + 1 < size) {
            buffer[length++] = (char)ch;
        } else {
            truncated = 1;
        }

        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != EOF && ch != ' ' && ch != '\t' && ch != '\n' &&
             ch != '\r' && ch != '\f' && ch != '\v');

    buffer[length] = '\0';
    return !truncated;
}

static int add_i64(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL ||
        (b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int max_sum_no_three_consecutive(const int64_t *values,
                                        size_t count,
                                        int64_t *result)
{
    int64_t previous[3] = {0, 0, 0};
    int64_t current[3];

    if (result == NULL || (values == NULL && count != 0)) {
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        current[0] = previous[0];

        if (previous[1] > current[0]) {
            current[0] = previous[1];
        }
        if (previous[2] > current[0]) {
            current[0] = previous[2];
        }

        if (!add_i64(previous[0], values[i], &current[1]) ||
            !add_i64(previous[1], values[i], &current[2])) {
            return 0;
        }

        previous[0] = current[0];
        previous[1] = current[1];
        previous[2] = current[2];
    }

    *result = previous[0];

    if (previous[1] > *result) {
        *result = previous[1];
    }
    if (previous[2] > *result) {
        *result = previous[2];
    }

    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[128];
    size_t count;
    int64_t *values = NULL;
    int64_t result;

    if (!read_token(token, sizeof(token)) || !parse_size(token, &count)) {
        fputs("Invalid element count\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (count != 0) {
        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_token(token, sizeof(token)) ||
            !parse_i64(token, &values[i])) {
            fputs("Invalid element\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (!max_sum_no_three_consecutive(values, count, &result)) {
        fputs("Unable to calculate the result\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}