#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

static int compare_int64(const void *lhs, const void *rhs)
{
    const int64_t a = *(const int64_t *)lhs;
    const int64_t b = *(const int64_t *)rhs;

    return (a > b) - (a < b);
}

static int read_token(char *buffer, size_t size)
{
    int ch;
    size_t length = 0;

    if (buffer == NULL || size < 2) {
        return -1;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        if (ch == EOF) {
            return -1;
        }
    } while (isspace((unsigned char)ch));

    do {
        if (length + 1 >= size) {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = getchar()) != EOF &&
                   !isspace((unsigned char)ch)) {
            }
            return -1;
        }

        buffer[length++] = (char)ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != EOF && !isspace((unsigned char)ch));

    buffer[length] = '\0';
    return 0;
}

static int read_size(size_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *end;
    uintmax_t parsed;

    if (value == NULL || read_token(buffer, sizeof(buffer)) != 0) {
        return -1;
    }

    if (buffer[0] == '-') {
        return -1;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > SIZE_MAX) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_int64(int64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *end;
    intmax_t parsed;

    if (value == NULL || read_token(buffer, sizeof(buffer)) != 0) {
        return -1;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return -1;
    }

    *value = (int64_t)parsed;
    return 0;
}

static int read_array(int64_t *array, size_t length)
{
    if (array == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if (read_int64(&array[i]) != 0) {
            return -1;
        }
    }

    return 0;
}

static uint64_t absolute_difference(int64_t a, int64_t b)
{
    if (a >= b) {
        return (uint64_t)a - (uint64_t)b;
    }

    return (uint64_t)b - (uint64_t)a;
}

static int minimum_absolute_difference_sum(int64_t *a, int64_t *b,
                                           size_t length, uint64_t *result)
{
    uint64_t sum = 0;

    if (a == NULL || b == NULL || result == NULL || length == 0) {
        return -1;
    }

    qsort(a, length, sizeof(*a), compare_int64);
    qsort(b, length, sizeof(*b), compare_int64);

    for (size_t i = 0; i < length; ++i) {
        const uint64_t difference = absolute_difference(a[i], b[i]);

        if (difference > UINT64_MAX - sum) {
            return -1;
        }

        sum += difference;
    }

    *result = sum;
    return 0;
}

int main(void)
{
    size_t length;
    int64_t *a = NULL;
    int64_t *b = NULL;
    uint64_t result;
    int status = EXIT_FAILURE;

    if (read_size(&length) != 0 || length == 0 ||
        length > SIZE_MAX / sizeof(*a)) {
        goto cleanup;
    }

    a = malloc(length * sizeof(*a));
    b = malloc(length * sizeof(*b));

    if (a == NULL || b == NULL) {
        goto cleanup;
    }

    if (read_array(a, length) != 0 ||
        read_array(b, length) != 0) {
        goto cleanup;
    }

    if (minimum_absolute_difference_sum(a, b, length, &result) != 0) {
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(b);
    free(a);
    return status;
}