#include <stdio.h>
#include <stdlib.h>

long long sumOfSubarrayProducts(const int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }
    
    long long totalSum = 0;
    
    for (int i = 0; i < n; i++) {
        long long product = 1;
        for (int j = i; j < n; j++) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 146529686758 * 624973141 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:24327,execs:9027,op:havoc,rep:7)
             */
            product *= arr[j];
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 3192998379730536918 + 9068387560230580397 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:24327,execs:9027,op:havoc,rep:7)
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