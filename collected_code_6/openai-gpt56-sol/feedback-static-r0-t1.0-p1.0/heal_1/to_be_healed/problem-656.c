#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int compare_int64(const void *lhs, const void *rhs)
{
    const int64_t a = *(const int64_t *)lhs;
    const int64_t b = *(const int64_t *)rhs;

    return (a > b) - (a < b);
}

static int minimum_absolute_difference_sum(const int64_t *a, const int64_t *b,
                                           size_t length, uint64_t *result)
{
    int64_t *sorted_a = NULL;
    int64_t *sorted_b = NULL;
    uint64_t sum = 0U;
    size_t i;

    if (result == NULL || (length > 0U && (a == NULL || b == NULL))) {
        return -1;
    }

    if (length == 0U) {
        *result = 0U;
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*sorted_a)) {
        return -1;
    }

    sorted_a = malloc(length * sizeof(*sorted_a));
    sorted_b = malloc(length * sizeof(*sorted_b));

    if (sorted_a == NULL || sorted_b == NULL) {
        free(sorted_a);
        free(sorted_b);
        return -1;
    }

    for (i = 0U; i < length; ++i) {
        sorted_a[i] = a[i];
        sorted_b[i] = b[i];
    }

    qsort(sorted_a, length, sizeof(*sorted_a), compare_int64);
    qsort(sorted_b, length, sizeof(*sorted_b), compare_int64);

    for (i = 0U; i < length; ++i) {
        uint64_t difference;

        if (sorted_a[i] >= sorted_b[i]) {
            difference = (uint64_t)sorted_a[i] - (uint64_t)sorted_b[i];
        } else {
            difference = (uint64_t)sorted_b[i] - (uint64_t)sorted_a[i];
        }

        if (UINT64_MAX - sum < difference) {
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
    int64_t *a = NULL;
    int64_t *b = NULL;
    uint64_t result;
    size_t i;
    int status = EXIT_FAILURE;

    if (scanf("%zu", &length) != 1) {
        fprintf(stderr, "Invalid array length.\n");
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*a)) {
        fprintf(stderr, "Array length is too large.\n");
        return EXIT_FAILURE;
    }

    if (length > 0U) {
        a = malloc(length * sizeof(*a));
        b = malloc(length * sizeof(*b));

        if (a == NULL || b == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            goto cleanup;
        }
    }

    for (i = 0U; i < length; ++i) {
        /* Possible weaknesses found:
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
        if (scanf("%" SCNd64, &a[i]) != 1) {
            fprintf(stderr, "Invalid element in the first array.\n");
            goto cleanup;
        }
    }

    for (i = 0U; i < length; ++i) {
        /* Possible weaknesses found:
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
        if (scanf("%" SCNd64, &b[i]) != 1) {
            fprintf(stderr, "Invalid element in the second array.\n");
            goto cleanup;
        }
    }

    errno = 0;
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