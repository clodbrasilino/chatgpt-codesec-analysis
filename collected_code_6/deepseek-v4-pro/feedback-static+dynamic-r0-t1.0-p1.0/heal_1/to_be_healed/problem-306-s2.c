#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int max_sum_increasing_subsequence_prefix_with_k(int arr[], int n, int k) {
    if (arr == NULL || n <= 0 || k < 0 || k >= n) {
        return -1;
    }

    int *dp = (int *)malloc(n * sizeof(int));
    if (dp == NULL) {
        return -1;
    }

    for (int i = 0; i < n; i++) {
        dp[i] = arr[i];
    }

    int max_sum = arr[k];

    for (int i = 0; i < k; i++) {
        if (arr[i] < arr[k]) {
            dp[i] = arr[i];
            for (int j = 0; j < i; j++) {
                if (arr[j] < arr[i] && dp[j] + arr[i] > dp[i]) {
                    dp[i] = dp[j] + arr[i];
                }
            }
            if (dp[i] + arr[k] > max_sum) {
                max_sum = dp[i] + arr[k];
            }
        }
    }

    free(dp);
    return max_sum;
}

int main() {
    int arr[] = {1, 101, 2, 3, 100, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 4;

    int result = max_sum_increasing_subsequence_prefix_with_k(arr, n, k);
    if (result != -1) {
        printf("%d\n", result);
    } else {
        printf("Invalid input\n");
    }

    return 0;
}