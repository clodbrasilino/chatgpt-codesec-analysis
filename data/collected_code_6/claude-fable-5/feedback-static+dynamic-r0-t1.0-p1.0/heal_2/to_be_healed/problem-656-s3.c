#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int compare_ints(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y) {
        return -1;
    }
    if (x > y) {
        return 1;
    }
    return 0;
}

static int min_abs_diff_sum(const int *arr1, const int *arr2, size_t n, long long *result)
{
    int *sorted1 = NULL;
    int *sorted2 = NULL;
    long long sum = 0;
    size_t i;
    size_t bytes;

    if (arr1 == NULL || arr2 == NULL || result == NULL || n == 0) {
        return -1;
    }

    if (n > SIZE_MAX / sizeof(*sorted1)) {
        return -1;
    }

    bytes = n * sizeof(*sorted1);

    sorted1 = malloc(bytes);
    if (sorted1 == NULL) {
        return -1;
    }

    sorted2 = malloc(bytes);
    if (sorted2 == NULL) {
        free(sorted1);
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(sorted1, arr1, bytes);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(sorted2, arr2, bytes);

    qsort(sorted1, n, sizeof(*sorted1), compare_ints);
    qsort(sorted2, n, sizeof(*sorted2), compare_ints);

    for (i = 0; i < n; i++) {
        long long diff = (long long)sorted1[i] - (long long)sorted2[i];
        if (diff < 0) {
            diff = -diff;
        }
        sum += diff;
    }

    free(sorted1);
    free(sorted2);

    *result = sum;
    return 0;
}

int main(void)
{
    const int arr1[] = {4, 1, 8, 7};
    const int arr2[] = {2, 3, 6, 5};
    size_t n = sizeof(arr1) / sizeof(arr1[0]);
    long long result = 0;

    if (min_abs_diff_sum(arr1, arr2, n, &result) != 0) {
        fprintf(stderr, "Error computing minimum sum of absolute differences\n");
        return EXIT_FAILURE;
    }

    printf("Minimum sum of absolute differences: %lld\n", result);
    return EXIT_SUCCESS;
}