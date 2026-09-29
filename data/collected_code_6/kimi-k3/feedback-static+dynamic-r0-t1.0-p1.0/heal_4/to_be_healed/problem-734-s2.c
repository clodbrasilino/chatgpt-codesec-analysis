#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

long long sumOfSubarrayProducts(const int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }
    
    long long totalSum = 0;
    
    for (int i = 0; i < n; i++) {
        long long product = 1;
        for (int j = i; j < n; j++) {
            if (arr[j] != 0 && product > LLONG_MAX / llabs((long long)arr[j])) {
                product = LLONG_MAX;
            } else if (arr[j] != 0 && product < LLONG_MIN / llabs((long long)arr[j])) {
                product = LLONG_MIN;
            } else {
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: -9223372036854775808 * -1 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000018,time:28354,execs:30543,op:havoc,rep:4)
                 */
                product *= arr[j];
            }
            
            if (product > 0 && totalSum > LLONG_MAX - product) {
                totalSum = LLONG_MAX;
            } else if (product < 0 && totalSum < LLONG_MIN - product) {
                totalSum = LLONG_MIN;
            } else {
                totalSum += product;
            }
        }
    }
    
    return totalSum;
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if ((size_t)n > SIZE_MAX / sizeof(int)) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    int *arr = malloc((size_t)n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(arr);
            return EXIT_FAILURE;
        }
    }
    
    long long result = sumOfSubarrayProducts(arr, n);
    printf("%lld\n", result);
    
    free(arr);
    return EXIT_SUCCESS;
}