#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int longest_subsequence(int arr[], int n, int *result) {
    if (n <= 0) {
        return 0;
    }

    int *dp = (int *)malloc(n * sizeof(int));
    int *prev = (int *)malloc(n * sizeof(int));
    int max_len = 1;
    int max_idx = 0;

    for (int i = 0; i < n; i++) {
        dp[i] = 1;
        prev[i] = -1;
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (abs(arr[i] - arr[j]) == 1 && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                prev[i] = j;
            }
        }
        if (dp[i] > max_len) {
            max_len = dp[i];
            max_idx = i;
        }
    }

    int idx = max_idx;
    for (int i = max_len - 1; i >= 0; i--) {
        result[i] = arr[idx];
        idx = prev[idx];
    }

    free(dp);
    free(prev);
    return max_len;
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 3, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int *result = (int *)malloc(n * sizeof(int));
    
    int len = longest_subsequence(arr, n, result);

    printf("Length of longest subsequence: %d\n", len);
    printf("Subsequence: ");
    for (int i = 0; i < len; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return 0;
}