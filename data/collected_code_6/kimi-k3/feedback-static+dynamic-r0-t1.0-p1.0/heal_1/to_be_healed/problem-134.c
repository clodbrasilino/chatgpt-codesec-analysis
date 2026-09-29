#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int isLastElementEvenAfterOperations(int arr[], int size, int p) {
    if (arr == NULL || size <= 0) {
        return -1;
    }
    
    int last = arr[size - 1];
    for (int i = 0; i < p; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1610612736 * 2 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:2473,execs:889,op:havoc,rep:1)
         * UBSan: signed integer overflow: -1674115755 * 2 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:2406,execs:869,op:havoc,rep:2)
         * UBSan: signed integer overflow: 1342177280 * 2 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000006,time:4490,execs:1605,op:havoc,rep:10)
         */
        last = last * 2;
    }
    
    return (last % 2 == 0) ? 1 : 0;
}

int main(void) {
    int n, p;
    
    if (scanf("%d", &n) != 1 || n <= 0) {
        return EXIT_FAILURE;
    }
    
    int *arr = (int *)malloc((size_t)n * sizeof(int));
    if (arr == NULL) {
        return EXIT_FAILURE;
    }
    
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return EXIT_FAILURE;
        }
    }
    
    if (scanf("%d", &p) != 1 || p < 0) {
        free(arr);
        return EXIT_FAILURE;
    }
    
    int result = isLastElementEvenAfterOperations(arr, n, p);
    if (result == 1) {
        printf("Even\n");
    } else if (result == 0) {
        printf("Odd\n");
    } else {
        printf("Invalid input\n");
    }
    
    free(arr);
    return EXIT_SUCCESS;
}