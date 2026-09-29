#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int maxSumIncreasingSubsequence(int* arr, int n, int i, int k) {
    if (arr == NULL || n <= 0 || i < 0 || k <= i || k >= n) {
        return -1;
    }

    int* dp = (int*)malloc((i + 1) * sizeof(int));
    if (dp == NULL) {
        return -1;
    }

    for (int j = 0; j <= i; j++) {
        dp[j] = arr[j];
    }

    for (int j = 1; j <= i; j++) {
        for (int m = 0; m < j; m++) {
            if (arr[j] > arr[m] && dp[j] < dp[m] + arr[j]) {
                dp[j] = dp[m] + arr[j];
            }
        }
    }

    int max_sum = -1;
    for (int j = 0; j <= i; j++) {
        if (arr[k] > arr[j]) {
            int current_sum = dp[j] + arr[k];
            if (current_sum > max_sum) {
                max_sum = current_sum;
            }
        }
    }

    if (max_sum == -1) {
        max_sum = arr[k]; 
    }

    free(dp);
    return max_sum;
}

int main() {
    int arr[] = {1, 101, 2, 3, 100, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i = 3;
    int k = 4;

    int result = maxSumIncreasingSubsequence(arr, n, i, k);
    if (result != -1) {
        printf("%d\n", result);
    } else {
        printf("Invalid input or memory allocation failed.\n");
    }

    return 0;
}