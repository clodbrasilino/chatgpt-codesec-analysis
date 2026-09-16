#include <stdio.h>
#include <limits.h>

int maxDifference(const int arr[], int n) {
    if (n <= 1) return 0;
    int min_val = arr[0];
    int max_diff = INT_MIN;
    for (int i = 1; i < n; i++) {
        if (arr[i] - min_val > max_diff) {
            max_diff = arr[i] - min_val;
        }
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }
    return max_diff;
}

int main() {
    const int arr[] = {2, 3, 10, 6, 4, 8, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = maxDifference(arr, n);
    printf("Maximum difference is %d\n", result);
    return 0;
}