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

int largest_divisible_subset(const int *input, size_t n, int **result, size_t *result_size)
{
    int *arr = NULL;
    int *dp = NULL;
    int *prev = NULL;
    int *subset = NULL;
    size_t i;
    size_t j;
    size_t best_index = 0;
    size_t best_len = 0;
    size_t k;
    int idx;

    if (input == NULL || result == NULL || result_size == NULL || n == 0) {
        return -1;
    }

    arr = malloc(n * sizeof(*arr));
    if (arr == NULL) {
        return -1;
    }

    dp = malloc(n * sizeof(*dp));
    if (dp == NULL) {
        free(arr);
        return -1;
    }

    prev = malloc(n * sizeof(*prev));
    if (prev == NULL) {
        free(arr);
        free(dp);
        return -1;
    }

    for (i = 0; i < n; i++) {
        arr[i] = input[i];
    }

    qsort(arr, n, sizeof(*arr), compare_ints);

    for (i = 0; i < n; i++) {
        dp[i] = 1;
        prev[i] = -1;
        for (j = 0; j < i; j++) {
            if (arr[j] != 0 && (arr[i] % arr[j]) == 0 && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                prev[i] = (int)j;
            }
        }
        if ((size_t)dp[i] > best_len) {
            best_len = (size_t)dp[i];
            best_index = i;
        }
    }

    subset = malloc(best_len * sizeof(*subset));
    if (subset == NULL) {
        free(arr);
        free(dp);
        free(prev);
        return -1;
    }

    k = best_len;
    idx = (int)best_index;
    while (idx >= 0 && k > 0) {
        k--;
        subset[k] = arr[idx];
        idx = prev[idx];
    }

    free(arr);
    free(dp);
    free(prev);

    *result = subset;
    *result_size = best_len;
    return 0;
}

int main(void)
{
    int numbers[] = {1, 2, 3, 4, 8, 16, 5, 9, 18};
    size_t n = sizeof(numbers) / sizeof(numbers[0]);
    int *subset = NULL;
    size_t subset_size = 0;
    size_t i;

    if (largest_divisible_subset(numbers, n, &subset, &subset_size) != 0) {
        fprintf(stderr, "Failed to compute largest divisible subset\n");
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