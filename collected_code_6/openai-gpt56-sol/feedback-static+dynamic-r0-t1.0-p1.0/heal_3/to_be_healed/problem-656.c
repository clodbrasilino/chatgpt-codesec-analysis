#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>

static int compare_int64(const void *lhs, const void *rhs)
{
    const int64_t a = *(const int64_t *)lhs;
    const int64_t b = *(const int64_t *)rhs;

    return (a > b) - (a < b);
}

static int read_line(char *buffer, size_t size)
{
    if (buffer == NULL || size < 2 || fgets(buffer, size, stdin) == NULL) {
        return -1;
    }

    if (strchr(buffer, '\n') == NULL) {
        if (!feof(stdin)) {
            int ch;

            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);

            return -1;
        }
    }

    return 0;
}

static int read_int64(int64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *start;
    char *end;
    intmax_t parsed;

    if (value == NULL || read_line(buffer, sizeof(buffer)) != 0) {
        return -1;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0') {
        return -1;
    }

    errno = 0;
    parsed = strtoimax(start, &end, 10);

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
    char buffer[256];
    char *start;
    char *end;
    uintmax_t parsed;

    if (value == NULL || read_line(buffer, sizeof(buffer)) != 0) {
        return -1;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

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

static uint64_t absolute_difference(int64_t a, int64_t b)
{
    if (a >= b) {
        return (uint64_t)a - (uint64_t)b;
    }

    return (uint64_t)b - (uint64_t)a;
}

static int minimum_absolute_difference_sum(const int64_t *a,
                                           const int64_t *b,
                                           size_t length,
                                           uint64_t *result)
{
    int64_t *sorted_a = NULL;
    int64_t *sorted_b = NULL;
    uint64_t sum = 0;
    size_t allocation_size;
    size_t i;

    if (result == NULL || (length > 0 && (a == NULL || b == NULL))) {
        return -1;
    }

    if (length == 0) {
        *result = 0;
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*sorted_a)) {
        return -1;
    }

    allocation_size = length * sizeof(*sorted_a);
    sorted_a = malloc(allocation_size);
    sorted_b = malloc(allocation_size);

    if (sorted_a == NULL || sorted_b == NULL) {
        free(sorted_a);
        free(sorted_b);
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(sorted_a, a, allocation_size);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(sorted_b, b, allocation_size);

    qsort(sorted_a, length, sizeof(*sorted_a), compare_int64);
    qsort(sorted_b, length, sizeof(*sorted_b), compare_int64);

    for (i = 0; i < length; ++i) {
        uint64_t difference =
            absolute_difference(sorted_a[i], sorted_b[i]);

        if (difference > UINT64_MAX - sum) {
            free(sorted_a);
            free(sorted_b);
            return -1;
        }

        sum += difference;
    }

    free(sorted_a);
    free(sorted_b);
    *result = sum;
    return 0;
}

int main(void)
{
    size_t length;
    size_t allocation_size;
    int64_t *a = NULL;
    int64_t *b = NULL;
    uint64_t result;
    size_t i;
    int status = EXIT_FAILURE;

    if (read_size(&length) != 0) {
        fprintf(stderr, "Invalid array length.\n");
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*a)) {
        fprintf(stderr, "Array length is too large.\n");
        return EXIT_FAILURE;
    }

    if (length > 0) {
        allocation_size = length * sizeof(*a);
        a = malloc(allocation_size);
        b = malloc(allocation_size);

        if (a == NULL || b == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            goto cleanup;
        }
    }

    for (i = 0; i < length; ++i) {
        if (read_int64(&a[i]) != 0) {
            fprintf(stderr, "Invalid element in the first array.\n");
            goto cleanup;
        }
    }

    for (i = 0; i < length; ++i) {
        if (read_int64(&b[i]) != 0) {
            fprintf(stderr, "Invalid element in the second array.\n");
            goto cleanup;
        }
    }

    if (minimum_absolute_difference_sum(a, b, length, &result) != 0) {
        fprintf(stderr, "Unable to calculate the result.\n");
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        fprintf(stderr, "Output error.\n");
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(a);
    free(b);
    return status;
}