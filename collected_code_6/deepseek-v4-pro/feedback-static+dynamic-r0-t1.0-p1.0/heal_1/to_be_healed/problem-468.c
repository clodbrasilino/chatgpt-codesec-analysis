#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
long long max_product_increasing_subsequence(int arr[], int n) {
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
            if (arr[j] < arr[i]) {
                dp[i] = MAX(dp[i], dp[j] * arr[i]);
            }
        }
        max_product = MAX(max_product, dp[i]);
    }

    free(dp);
    return max_product;
}

int main() {
    int arr1[] = {3, 2, 6, 4, 5, 1};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%lld\n", max_product_increasing_subsequence(arr1, n1));

    int arr2[] = {1, 2, 3, 4, 5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%lld\n", max_product_increasing_subsequence(arr2, n2));

    int arr3[] = {5, 4, 3, 2, 1};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%lld\n", max_product_increasing_subsequence(arr3, n3));

    int arr4[] = {2, 3, -2, 4};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("%lld\n", max_product_increasing_subsequence(arr4, n4));

    int arr5[] = {-2, -3, -1};
    int n5 = sizeof(arr5) / sizeof(arr5[0]);
    printf("%lld\n", max_product_increasing_subsequence(arr5, n5));

    return 0;
}