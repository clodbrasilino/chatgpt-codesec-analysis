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
            long long val = (long long)arr[j];
            
            if (val != 0) {
                if (val == -1 && product == LLONG_MIN) {
                    product = LLONG_MAX;
                } else if (product > 0 && val > 0 && product > LLONG_MAX / val) {
                    product = LLONG_MAX;
                /* Possible weaknesses found:
                 * ASan: FPE (AFL crash: id:000001,sig:06,src:000012,time:8107,execs:9207,op:havoc,rep:5)
                 * UBSan: division of -9223372036854775808 by -1 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000012,time:8107,execs:9207,op:havoc,rep:5)
                 */
                } else if (product > 0 && val < 0 && product > LLONG_MIN / val) {
                    product = LLONG_MIN;
                } else if (product < 0 && val > 0 && product < LLONG_MIN / val) {
                    product = LLONG_MIN;
                } else if (product < 0 && val < 0 && product < LLONG_MAX / val) {
                    product = LLONG_MAX;
                } else {
                    product *= val;
                }
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
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000005,time:7288,execs:8356,op:havoc,rep:2; likely memory-safety defect
  */

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