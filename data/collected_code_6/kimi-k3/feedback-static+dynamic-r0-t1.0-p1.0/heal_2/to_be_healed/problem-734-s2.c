#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 5, got <no output>
  *  test case 0 failed: expected 20, got <no output>
  *  test case 2 failed: expected 84, got <no output>
  */

long long sumOfSubarrayProducts(const int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }
    
    long long totalSum = 0;
    
    for (int i = 0; i < n; i++) {
        long long product = 1;
        for (int j = i; j < n; j++) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 5860100855664 * 149477148 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000010,time:11755,execs:4672,op:havoc,rep:4)
             */
            product *= arr[j];
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 8954201229096669058 + 8415830224286769344 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000010,time:11755,execs:4672,op:havoc,rep:4)
             */
            totalSum += product;
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
    
    int *arr = malloc(n * sizeof(int));
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