#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int find_max_sum(int arr[], int n, int i, int k) {
    if (k <= i || k >= n || i < 0) {
        return -1;
    }

    int *dp = (int *)malloc(n * sizeof(int));
    if (dp == NULL) {
        return -1;
    }

    for (int j = 0; j < n; j++) {
        dp[j] = arr[j];
    }

    for (int j = 1; j < n; j++) {
        for (int p = 0; p < j; p++) {
            if (arr[p] < arr[j]) {
                if (dp[p] + arr[j] > dp[j]) {
                    dp[j] = dp[p] + arr[j];
                }
            }
        }
    }

    if (dp[i] == arr[i] && i > 0) {
        for (int p = 0; p < i; p++) {
            if (arr[p] < arr[i]) {
                if (dp[p] + arr[i] > dp[i]) {
                    dp[i] = dp[p] + arr[i];
                }
            }
        }
    }

    int max_sum = -1;
    for (int j = 0; j <= i; j++) {
        if (arr[j] < arr[k]) {
            if (dp[j] > max_sum) {
                max_sum = dp[j];
            }
        }
    }

    free(dp);
    return (max_sum == -1) ? -1 : max_sum + arr[k];
}

int main() {
    int arr[] = {1, 101, 2, 3, 100, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i = 4;
    int k = 6;

    int result = find_max_sum(arr, n, i, k);

    printf("%d\n", result);

    return 0;
}