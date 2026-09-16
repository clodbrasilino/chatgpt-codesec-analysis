#include <stdio.h>
#include <stdlib.h>

long long findMaxProduct(int* arr, int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }
    if (n == 1) {
        return (long long)arr[0];
    }
    
    long long* dp = (long long*)malloc(n * sizeof(long long));
    if (dp == NULL) {
        return 0;
    }
    
    for (int i = 0; i < n; i++) {
        dp[i] = (long long)arr[i];
    }
    
    long long maxProduct = dp[0];
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i]) {
                long long product = dp[j] * (long long)arr[i];
                if (product > dp[i]) {
                    dp[i] = product;
                }
            }
        }
        if (dp[i] > maxProduct) {
            maxProduct = dp[i];
        }
    }
    
    free(dp);
    return maxProduct;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char* const argv[]) {
    if (argc < 2) {
        return 1;
    }
    
    int n = argc - 1;
    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }
    
    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i + 1]);
    }
    
    long long result = findMaxProduct(arr, n);
    printf("%lld\n", result);
    
    free(arr);
    return 0;
}