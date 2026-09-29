#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int longestSubsequence(int* arr, int n) {
    if (n == 0) return 0;

    int* dp = (int*)malloc(n * sizeof(int));
    if (dp == NULL) {
        return -1;
    }

    for (int i = 0; i < n; i++) {
        dp[i] = 1;
    }

    int max_len = 1;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if ((arr[i] == arr[j] + 1) || (arr[i] == arr[j] - 1)) {
                if (dp[i] < dp[j] + 1) {
                    dp[i] = dp[j] + 1;
                }
            }
        }
        if (max_len < dp[i]) {
            max_len = dp[i];
        }
    }

    free(dp);
    return max_len;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 3, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    int result = longestSubsequence(arr, n);
    if (result != -1) {
        printf("%d\n", result);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    return 0;
}