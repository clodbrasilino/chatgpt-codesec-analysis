#include <stdio.h>
#include <stdlib.h>

int isSubsetSum(const int arr[], int n, int sum) {
    size_t row_size = (size_t)(sum + 1);
    size_t total_size = (size_t)(n + 1) * row_size;
    int *subset = (int *)malloc(total_size * sizeof(int));
    if (subset == NULL) {
        return -1;
    }

    for (int i = 0; i <= n; i++) {
        subset[(size_t)i * row_size + 0] = 1;
    }

    for (int i = 1; i <= sum; i++) {
        subset[0 * row_size + (size_t)i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= sum; j++) {
            if (arr[i - 1] > j) {
                subset[(size_t)i * row_size + (size_t)j] = subset[(size_t)(i - 1) * row_size + (size_t)j];
            } else {
                subset[(size_t)i * row_size + (size_t)j] = subset[(size_t)(i - 1) * row_size + (size_t)j] || subset[(size_t)(i - 1) * row_size + (size_t)(j - arr[i - 1])];
            }
        }
    }

    int result = subset[(size_t)n * row_size + (size_t)sum];
    free(subset);
    return result;
}

int main(int argc, char * const argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <sum> <n> <elements...>\n", argv[0]);
        return 1;
    }

    char *endptr;
    long target_sum = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || target_sum < 0 || target_sum > 2147483647) {
        fprintf(stderr, "Invalid sum\n");
        return 1;
    }

    long n = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' || n < 0 || n > 2147483647 || n != argc - 3) {
        fprintf(stderr, "Invalid n or element count mismatch\n");
        return 1;
    }

    int *arr = (int *)malloc((size_t)n * sizeof(int));
    if (arr == NULL && n > 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        long val = strtol(argv[3 + i], &endptr, 10);
        if (*endptr != '\0' || val < 0 || val > 2147483647) {
            fprintf(stderr, "Invalid element\n");
            free(arr);
            return 1;
        }
        arr[i] = (int)val;
    }

    int result = isSubsetSum(arr, (int)n, (int)target_sum);
    printf("%d\n", result);

    free(arr);
    return 0;
}