#include <stdio.h>
#include <stdlib.h>

int max_sum_increasing_subsequence(const int *arr, int n, int i, int k) {
    if (arr == NULL || n <= 0 || i < 0 || k < 0 || i >= n || k >= n || k < i) {
        return 0;
    }

    int *dp = (int *)malloc(n * sizeof(int));
    if (dp == NULL) {
        return 0;
    }

    for (int j = 0; j < n; j++) {
        dp[j] = arr[j];
    }

    for (int j = 1; j < n; j++) {
        for (int l = 0; l < j; l++) {
            if (arr[j] > arr[l]) {
                if (dp[l] + arr[j] > dp[j]) {
                    dp[j] = dp[l] + arr[j];
                }
            }
        }
    }

    int sum = 0;
    int prev = -1;

    for (int j = i; j <= k; j++) {
        if (prev == -1 || arr[j] > prev) {
            /* Possible weaknesses found:
             *  each undeclared identifier is reported only once for each function it appears in
             *  use of undeclared identifier 'prev_index'
             *  'prev_index' undeclared (first use in this function)
             */
            if (dp[j] == arr[j] || (prev != -1 && dp[j] == dp[prev_index] + arr[j])) {
                sum += arr[j];
                prev = arr[j];
                /* Possible weaknesses found:
                 *  use of undeclared identifier 'prev_index'
                 */
                prev_index = j;
            }
        }
    }

    free(dp);
    return sum;
}

int main() {
    int arr1[] = {1, 101, 2, 3, 100, 4, 5};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int result1 = max_sum_increasing_subsequence(arr1, n1, 0, 1);
    printf("%d\n", result1);

    int arr2[] = {1, 101, 2, 3, 100, 4, 5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int result2 = max_sum_increasing_subsequence(arr2, n2, 2, 3);
    printf("%d\n", result2);

    int arr3[] = {1, 101, 2, 3, 100, 4, 5};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int result3 = max_sum_increasing_subsequence(arr3, n3, 4, 6);
    printf("%d\n", result3);

    return 0;
}