#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

long long sum_of_products_of_subarrays(const int *arr, int n) {
    long long total_sum = 0;
    for (int i = 0; i < n; i++) {
        long long current_product = 1;
        for (int j = i; j < n; j++) {
            /* Possible weaknesses found:
             * UBSan: division by zero (AFL crash: id:000001,sig:06,src:000006,time:7060,execs:2347,op:havoc,rep:2)
             * ASan: FPE (AFL crash: id:000001,sig:06,src:000006,time:7060,execs:2347,op:havoc,rep:2)
             */
            if (current_product > LLONG_MAX / (arr[j] >= 0 ? arr[j] : -arr[j]) ||
                (arr[j] < 0 && current_product < LLONG_MIN / (-arr[j])) ||
                (arr[j] > 0 && current_product < LLONG_MIN / arr[j])) {
                /* Possible weaknesses found:
                 *  Variable 'current_product' is assigned a value that is never used. [unreadVariable]
                 *  Value stored to 'current_product' is never read [deadcode.DeadStores]
                 */
                current_product = 1;
                break;
            }
            current_product *= arr[j];
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: -8251401944285471526 + -2062850484676271420 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000008,time:21136,execs:6840,op:havoc,rep:3)
             */
            total_sum += current_product;
        }
    }
    return total_sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:5141,execs:1705,op:havoc,rep:2; likely memory-safety defect
  */

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Error: Invalid input size.\n");
        return EXIT_FAILURE;
    }

    int *arr = (int *)malloc((size_t)n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Error: Invalid array element.\n");
            free(arr);
            return EXIT_FAILURE;
        }
    }

    long long result = sum_of_products_of_subarrays(arr, n);
    printf("%lld\n", result);

    free(arr);
    return EXIT_SUCCESS;
}