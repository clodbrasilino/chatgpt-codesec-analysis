#include <stdio.h>
#include <stdlib.h>

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

int largest_divisible_subset(const int *nums, size_t n, int **result, size_t *result_size)
{
    int *sorted = NULL;
    int *dp = NULL;
    int *prev = NULL;
    int *subset = NULL;
    size_t i;
    size_t j;
    size_t best_index = 0;
    size_t best_len = 0;
    size_t k;
    int idx;

    if (nums == NULL || result == NULL || result_size == NULL || n == 0) {
        return -1;
    }

    sorted = malloc(n * sizeof(int));
    if (sorted == NULL) {
        return -1;
    }

    dp = malloc(n * sizeof(int));
    if (dp == NULL) {
        free(sorted);
        return -1;
    }

    prev = malloc(n * sizeof(int));
    if (prev == NULL) {
        free(sorted);
        free(dp);
        return -1;
    }

    for (i = 0; i < n; i++) {
        sorted[i] = nums[i];
    }

    qsort(sorted, n, sizeof(int), compare_ints);

    for (i = 0; i < n; i++) {
        dp[i] = 1;
        prev[i] = -1;
        for (j = 0; j < i; j++) {
            if (sorted[j] != 0 && sorted[i] % sorted[j] == 0 && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                prev[i] = (int)j;
            }
        }
        if ((size_t)dp[i] > best_len) {
            best_len = (size_t)dp[i];
            best_index = i;
        }
    }

    subset = malloc(best_len * sizeof(int));
    if (subset == NULL) {
        free(sorted);
        free(dp);
        free(prev);
        return -1;
    }

    k = best_len;
    idx = (int)best_index;
    while (idx >= 0 && k > 0) {
        k--;
        subset[k] = sorted[idx];
        idx = prev[idx];
    }

    free(sorted);
    free(dp);
    free(prev);

    *result = subset;
    *result_size = best_len;
    return 0;
}

int main(void)
{
    int nums[] = {1, 2, 4, 8, 3, 9, 16, 5};
    size_t n = sizeof(nums) / sizeof(nums[0]);
    int *subset = NULL;
    size_t subset_size = 0;
    size_t i;

    if (largest_divisible_subset(nums, n, &subset, &subset_size) != 0) {
        fprintf(stderr, "Failed to compute subset\n");
        return EXIT_FAILURE;
    }

    printf("Largest divisible subset:");
    for (i = 0; i < subset_size; i++) {
        printf(" %d", subset[i]);
    }
    printf("\n");

    free(subset);
    return EXIT_SUCCESS;
}