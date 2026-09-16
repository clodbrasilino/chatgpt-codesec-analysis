#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int longestSubsequence(int arr[], int n) {
    if (n <= 0) {
        return 0;
    }

    int *dp = (int *)malloc(n * sizeof(int));
    if (dp == NULL) {
        return 0;
    }

    for (int i = 0; i < n; i++) {
        dp[i] = 1;
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (abs(arr[i] - arr[j]) == 1 && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
            }
        }
    }

    int max_len = 1;
    for (int i = 0; i < n; i++) {
        if (dp[i] > max_len) {
            max_len = dp[i];
        }
    }

    free(dp);
    return max_len;
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", longestSubsequence(arr1, n1));

    int arr2[] = {10, 9, 8, 7, 6};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", longestSubsequence(arr2, n2));

    int arr3[] = {1, 3, 5, 7, 9};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", longestSubsequence(arr3, n3));

    return 0;
}