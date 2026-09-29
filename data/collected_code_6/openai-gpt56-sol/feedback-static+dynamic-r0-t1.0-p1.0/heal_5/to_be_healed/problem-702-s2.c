#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (a > b) - (a < b);
}

static size_t minimum_removals(int *values, size_t count, int64_t k)
{
    if (values == NULL || count == 0) {
        return 0;
    }

    if (k < 0) {
        return count;
    }

    qsort(values, count, sizeof(*values), compare_ints);

    size_t left = 0;
    size_t max_kept = 1;

    for (size_t right = 0; right < count; ++right) {
        while ((int64_t)values[right] - (int64_t)values[left] > k) {
            ++left;
        }

        const size_t kept = right - left + 1;

        if (kept > max_kept) {
            max_kept = kept;
        }
    }

    return count - max_kept;
}

static int read_token(char *buffer, size_t size)
{
    if (buffer == NULL || size < 2) {
        return 0;
    }

    size_t length = 0;
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        if (ch == EOF) {
            return 0;
        }
    } while (ch == ' ' || ch == '\t' || ch == '\n' ||
             ch == '\r' || ch == '\f' || ch == '\v');

    do {
        if (length + 1 >= size) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = getchar();
            } while (ch != EOF && ch != ' ' && ch != '\t' &&
                     ch != '\n' && ch != '\r' && ch != '\f' &&
                     ch != '\v');

            buffer[0] = '\0';
            return 0;
        }

        buffer[length++] = (char)ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != EOF && ch != ' ' && ch != '\t' &&
             ch != '\n' && ch != '\r' && ch != '\f' &&
             ch != '\v');

    buffer[length] = '\0';
    return 1;
}

static int parse_size(const char *text, size_t *value)
{
    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return 0;
    }

    char *end = NULL;
    errno = 0;
    const uintmax_t parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int parse_int64(const char *text, int64_t *value)
{
    if (text == NULL || value == NULL || *text == '\0') {
        return 0;
    }

    char *end = NULL;
    errno = 0;
    const intmax_t parsed = strtoimax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static int parse_int(const char *text, int *value)
{
    if (text == NULL || value == NULL || *text == '\0') {
        return 0;
    }

    char *end = NULL;
    errno = 0;
    const intmax_t parsed = strtoimax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT_MIN || parsed > INT_MAX) {
        return 0;
    }

    *value = (int)parsed;
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[128];
    size_t count;
    int64_t k;

    if (!read_token(token, sizeof(token)) ||
        !parse_size(token, &count) ||
        !read_token(token, sizeof(token)) ||
        !parse_int64(token, &k)) {
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(int)) {
        return EXIT_FAILURE;
    }

    int *values = NULL;

    if (count != 0) {
        values = malloc(count * sizeof(*values));

        if (values == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_token(token, sizeof(token)) ||
            !parse_int(token, &values[i])) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    const size_t result = minimum_removals(values, count, k);

    if (printf("%zu\n", result) < 0) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}