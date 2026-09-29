#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

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

        size_t kept = right - left + 1;
        if (kept > max_kept) {
            max_kept = kept;
        }
    }

    return count - max_kept;
}

static int read_token(char *buffer, size_t size)
{
    if (buffer == NULL || size == 0) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    return scanf("%127s", buffer) == 1;
}

static int parse_size(const char *text, size_t *value)
{
    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return 0;
    }

    char *end = NULL;
    errno = 0;
    uintmax_t parsed = strtoumax(text, &end, 10);

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
    intmax_t parsed = strtoimax(text, &end, 10);

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
    intmax_t parsed = strtoimax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        /* Possible weaknesses found:
         *  'INT_MIN' undeclared (first use in this function)
         *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier 'INT_MIN'
         *  'INT_MAX' undeclared (first use in this function)
         *  use of undeclared identifier 'INT_MAX'
         */
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

    if (!read_token(token, sizeof(token)) || !parse_size(token, &count) ||
        !read_token(token, sizeof(token)) || !parse_int64(token, &k)) {
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

    size_t result = minimum_removals(values, count, k);

    if (printf("%zu\n", result) < 0) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}