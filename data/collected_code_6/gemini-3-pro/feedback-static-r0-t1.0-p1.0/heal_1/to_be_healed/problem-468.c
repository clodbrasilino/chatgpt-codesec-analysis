#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
long long findMaxProductIncreasingSubsequence(int* arr, int n) {
    if (arr == NULL || n <= 0) {
        return -1;
    }

    long long* dp = (long long*)malloc(n * sizeof(long long));
    if (dp == NULL) {
        return -1;
    }

    long long max_product = 0;

    for (int i = 0; i < n; i++) {
        dp[i] = arr[i];
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] && dp[i] < dp[j] * arr[i]) {
                dp[i] = dp[j] * arr[i];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (dp[i] > max_product) {
            max_product = dp[i];
        }
    }

    free(dp);
    return max_product;
}

int main(void) {
    int arr[] = {3, 100, 4, 5, 150, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    long long result = findMaxProductIncreasingSubsequence(arr, n);
    if (result != -1) {
        printf("%lld\n", result);
    } else {
        printf("Error\n");
    }

    return 0;
}