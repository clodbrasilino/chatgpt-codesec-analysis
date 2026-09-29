#include <stdio.h>
#include <stdlib.h>

int count_pairs(const int arr[], int n, int sum) {
    int count = 0;
    int i, j;
    
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 2062812957 + 293717788 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000013,time:42169,execs:17981,op:havoc,rep:2)
             */
            if (arr[i] + arr[j] == sum) {
                count++;
            }
        }
    }
    
    return count;
}

int main(void) {
    int n, sum, i;
    int *arr;
    int result;
    
    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }
    
    if (n <= 0) {
        return EXIT_FAILURE;
    }
    
    arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        return EXIT_FAILURE;
    }
    
    for (i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return EXIT_FAILURE;
        }
    }
    
    if (scanf("%d", &sum) != 1) {
        free(arr);
        return EXIT_FAILURE;
    }
    
    result = count_pairs(arr, n, sum);
    printf("%d\n", result);
    
    free(arr);
    
    return EXIT_SUCCESS;
}