#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <errno.h>

static int compare_int64(const void *lhs, const void *rhs)
{
    const int64_t a = *(const int64_t *)lhs;
    const int64_t b = *(const int64_t *)rhs;

    return (a > b) - (a < b);
}

static int read_int64(int64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *start;
    char *end;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (value == NULL || fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }

    if (buffer[0] != '\0') {
        size_t i = 0;

        while (buffer[i] != '\0' && buffer[i] != '\n') {
            ++i;
        }

        if (buffer[i] != '\n' && !feof(stdin)) {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            return -1;
        }
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    intmax_t parsed = strtoimax(start, &end, 10);

    if (start == end || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = (int64_t)parsed;
    return 0;
}

static int read_size(size_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *start;
    char *end;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (value == NULL || fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }

    if (buffer[0] != '\0') {
        size_t i = 0;

        while (buffer[i] != '\0' && buffer[i] != '\n') {
            ++i;
        }

        if (buffer[i] != '\n' && !feof(stdin)) {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            return -1;
        }
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        return -1;
    }

    errno = 0;
    uintmax_t parsed = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || parsed > SIZE_MAX) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = (size_t)parsed;
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

static int minimum_absolute_difference_sum(
    int64_t *first,
    int64_t *second,
    size_t length,
    uint64_t *result)
{
    uint64_t sum = 0;

    if (first == NULL || second == NULL || result == NULL) {
        return -1;
    }

    qsort(first, length, sizeof(*first), compare_int64);
    qsort(second, length, sizeof(*second), compare_int64);

    for (size_t i = 0; i < length; ++i) {
        uint64_t difference = absolute_difference(first[i], second[i]);

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
    int64_t *first = NULL;
    int64_t *second = NULL;
    uint64_t result;
    int status = EXIT_FAILURE;

    if (read_size(&length) != 0 || length == 0) {
        fputs("Invalid array length\n", stderr);
        goto cleanup;
    }

    if (length > SIZE_MAX / sizeof(*first)) {
        fputs("Array length is too large\n", stderr);
        goto cleanup;
    }

    first = malloc(length * sizeof(*first));
    second = malloc(length * sizeof(*second));

    if (first == NULL || second == NULL) {
        fputs("Memory allocation failed\n", stderr);
        goto cleanup;
    }

    if (read_array(first, length) != 0 ||
        read_array(second, length) != 0) {
        fputs("Invalid array input\n", stderr);
        goto cleanup;
    }

    if (minimum_absolute_difference_sum(
            first, second, length, &result) != 0) {
        fputs("Unable to compute result\n", stderr);
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        fputs("Output error\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(second);
    free(first);
    return status;
}