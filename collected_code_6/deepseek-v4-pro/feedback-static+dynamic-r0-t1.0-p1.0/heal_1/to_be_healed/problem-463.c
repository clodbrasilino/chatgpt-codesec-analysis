#include <stdio.h>
#include <stdlib.h>

int maxProductSubarray(int arr[], int n, int *start, int *end) {
    if (n <= 0 || arr == NULL) return 0;
    
    int max_product = arr[0];
    int min_product = arr[0];
    int global_max = arr[0];
    int current_start = 0;
    int max_start = 0;
    int max_end = 0;
    
    for (int i = 1; i < n; i++) {
        if (arr[i] < 0) {
            int temp = max_product;
            max_product = min_product;
            min_product = temp;
        }
        
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 80 * 149477144 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000010,time:5589,execs:2841,op:havoc,rep:4)
         * UBSan: signed integer overflow: -40 * -2062812956 cannot be represented in type 'int' (AFL crash: id:000003,sig:06,src:000010,time:15311,execs:7757,op:havoc,rep:5)
         * UBSan: signed integer overflow: -133333 * -43333330 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000010,time:14507,execs:7347,op:havoc,rep:3)
         * UBSan: signed integer overflow: 1795074732 * 1228654360 cannot be represented in type 'int' (AFL crash: id:000004,sig:06,src:000010,time:21136,execs:10658,op:havoc,rep:7)
         * UBSan: signed integer overflow: -1504771484 * 2132154344 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000010,time:10840,execs:5515,op:havoc,rep:5)
         */
        if (arr[i] > max_product * arr[i]) {
            max_product = arr[i];
            current_start = i;
        } else {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: -133333 * -43333330 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000010,time:14507,execs:7347,op:havoc,rep:3)
             * UBSan: signed integer overflow: 1795074732 * 1228654360 cannot be represented in type 'int' (AFL crash: id:000004,sig:06,src:000010,time:21136,execs:10658,op:havoc,rep:7)
             * UBSan: signed integer overflow: -40 * -2062812956 cannot be represented in type 'int' (AFL crash: id:000003,sig:06,src:000010,time:15311,execs:7757,op:havoc,rep:5)
             */
            max_product = max_product * arr[i];
        }
        
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 399999 * -43333330 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000010,time:14507,execs:7347,op:havoc,rep:3)
         * UBSan: signed integer overflow: -40 * 149477144 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000010,time:5589,execs:2841,op:havoc,rep:4)
         * UBSan: signed integer overflow: 1285418552 * -3 cannot be represented in type 'int' (AFL crash: id:000005,sig:06,src:000016,time:40195,execs:19982,op:havoc,rep:1)
         * UBSan: signed integer overflow: 598358244 * 1228654360 cannot be represented in type 'int' (AFL crash: id:000004,sig:06,src:000010,time:21136,execs:10658,op:havoc,rep:7)
         * UBSan: signed integer overflow: -1504771484 * 2132154344 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000010,time:10840,execs:5515,op:havoc,rep:5)
         */
        min_product = (arr[i] < min_product * arr[i]) ? arr[i] : min_product * arr[i];
        
        if (max_product > global_max) {
            global_max = max_product;
            max_start = current_start;
            max_end = i;
        }
    }
    
    *start = max_start;
    *end = max_end;
    return global_max;
}

int main(void) {
    int n;
    printf("Enter the size of array: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input\n");
        return 1;
    }
    
    int *arr = (int *)malloc((size_t)n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Invalid input\n");
            free(arr);
            return 1;
        }
    }
    
    int start = 0, end = 0;
    int result = maxProductSubarray(arr, n, &start, &end);
    
    printf("Maximum product subarray: ");
    for (int i = start; i <= end; i++) {
        printf("%d", arr[i]);
        if (i < end) printf(" ");
    }
    printf("\nMaximum product: %d\n", result);
    
    free(arr);
    return 0;
}