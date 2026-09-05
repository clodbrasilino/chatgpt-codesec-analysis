#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
long long max_product_increasing_subsequence(int *arr, int n) {
    if (n <= 0) {
        return 0;
    }

    long long *dp = (long long *)malloc(n * sizeof(long long));
    if (dp == NULL) {
        return 0;
    }

    long long max_product = 0;

    for (int i = 0; i < n; i++) {
        dp[i] = arr[i];
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] && dp[j] * arr[i] > dp[i]) {
                dp[i] = dp[j] * arr[i];
            }
        }
        if (dp[i] > max_product) {
            max_product = dp[i];
        }
    }

    free(dp);

    return max_product;
}

int main() {
    int arr1[] = {3, 4, 5, 1, 2};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    long long result1 = max_product_increasing_subsequence(arr1, n1);
    printf("%lld\n", result1);

    int arr2[] = {10, 2, 3, 9};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    long long result2 = max_product_increasing_subsequence(arr2, n2);
    printf("%lld\n", result2);

    int arr3[] = {-5, -4, -3, -2, -1};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    long long result3 = max_product_increasing_subsequence(arr3, n3);
    printf("%lld\n", result3);

    return 0;
}