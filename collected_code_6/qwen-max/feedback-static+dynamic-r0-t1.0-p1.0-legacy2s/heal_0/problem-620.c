#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int findLargestSubset(int *arr, int n) {
    qsort(arr, n, sizeof(int), compare);
    int dp[n];
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] % arr[j] == 0 && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
            }
        }
    }
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (dp[i] > max) {
            max = dp[i];
        }
    }
    return max;
}

int main() {
    int arr[] = {1, 2, 3, 4, 8, 9, 12, 16};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("The size of the largest subset is: %d\n", findLargestSubset(arr, n));
    return 0;
}