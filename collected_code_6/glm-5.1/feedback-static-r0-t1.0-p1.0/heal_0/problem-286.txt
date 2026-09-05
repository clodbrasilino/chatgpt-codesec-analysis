#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int maxSubarraySum(int* arr, int n, int k) {
    if (n == 0 || k == 0) {
        return 0;
    }

    int current_max = arr[0];
    int global_max = arr[0];
    long long total_sum = arr[0];

    for (int i = 1; i < n; i++) {
        total_sum += arr[i];
        current_max = max(arr[i], current_max + arr[i]);
        global_max = max(global_max, current_max);
    }

    if (k == 1) {
        return global_max;
    }

    for (int i = 0; i < n; i++) {
        current_max = max(arr[i], current_max + arr[i]);
        global_max = max(global_max, current_max);
    }

    if (total_sum > 0) {
        global_max = max(global_max, (int)(global_max + (k - 2) * total_sum));
    }

    return global_max;
}

int main() {
    int arr[] = {1, -2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 5;

    int result = maxSubarraySum(arr, n, k);

    printf("%d\n", result);

    return 0;
}