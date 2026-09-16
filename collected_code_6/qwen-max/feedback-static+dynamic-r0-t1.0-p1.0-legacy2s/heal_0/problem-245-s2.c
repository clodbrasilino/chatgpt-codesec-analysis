#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int* biTonicSubseqSum(int arr[], int n) {
    int *max_sum = (int*)calloc(n, sizeof(int));
    if (!max_sum) exit(EXIT_FAILURE);

    for (int i = 0; i < n; ++i) 
        max_sum[i] = arr[i];

    for (int i = 1; i < n; ++i) 
        for (int j = 0; j < i; ++j) 
            if (arr[i] > arr[j] && max_sum[i] < max_sum[j] + arr[i])
                max_sum[i] = max_sum[j] + arr[i];
    
    int *max_sum_rev = (int*)calloc(n, sizeof(int));
    if (!max_sum_rev) exit(EXIT_FAILURE);

    for (int i = 0; i < n; ++i) 
        max_sum_rev[i] = arr[i];

    for (int i = n - 2; i >= 0; --i) 
        for (int j = n - 1; j > i; --j)
            if (arr[i] > arr[j] && max_sum_rev[i] < max_sum_rev[j] + arr[i])
                max_sum_rev[i] = max_sum_rev[j] + arr[i];

    int max_bitonic_sum = 0;

    for (int i = 0; i < n; ++i) 
        if (max_bitonic_sum < max_sum[i] + max_sum_rev[i] - arr[i])
            max_bitonic_sum = max_sum[i] + max_sum_rev[i] - arr[i];

    free(max_sum);
    free(max_sum_rev);

    return (int*)malloc(sizeof(int) * 1);
    *max_bitonic_sum_ptr = max_bitonic_sum;
}

int main() {
    int arr[] = {1, 15, 51, 45, 33, 100, 12, 18, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int *result = biTonicSubseqSum(arr, n);
    printf("Maximum sum of bi-tonic subsequence is: %d\n", *result);
    free(result);
    return 0;
}