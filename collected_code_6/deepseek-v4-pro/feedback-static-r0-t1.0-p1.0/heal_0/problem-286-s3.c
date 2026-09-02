#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int maxSubarraySum(int *arr, int n) {
    int max_so_far = INT_MIN;
    int max_ending_here = 0;
    for (int i = 0; i < n; i++) {
        max_ending_here += arr[i];
        if (max_ending_here > max_so_far) {
            max_so_far = max_ending_here;
        }
        if (max_ending_here < 0) {
            max_ending_here = 0;
        }
    }
    return max_so_far;
}

int maxSubarraySumRepeated(int *arr, int n, int k) {
    int total_sum = 0;
    for (int i = 0; i < n; i++) {
        total_sum += arr[i];
    }

    if (k == 1) {
        return maxSubarraySum(arr, n);
    }

    int *doubled = (int *)malloc(2 * n * sizeof(int));
    if (doubled == NULL) {
        return -1;
    }
    for (int i = 0; i < n; i++) {
        doubled[i] = arr[i];
        doubled[i + n] = arr[i];
    }

    int max_doubled = maxSubarraySum(doubled, 2 * n);
    free(doubled);

    if (total_sum > 0) {
        return max_doubled + (k - 2) * total_sum;
    } else {
        return max_doubled;
    }
}

int main(void) {
    int arr[] = {-1, 4, -2, 3, -2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;
    int result = maxSubarraySumRepeated(arr, n, k);
    printf("%d\n", result);
    return 0;
}