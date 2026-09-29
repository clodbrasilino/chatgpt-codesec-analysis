#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

long long sum_of_products_of_subarrays(const int *arr, int n) {
    long long total_sum = 0;
    for (int i = 0; i < n; i++) {
        long long current_product = 1;
        for (int j = i; j < n; j++) {
            int val = arr[j];
            if (val == 0) {
                current_product = 1;
                total_sum += 0;
                continue;
            }
            
            int overflow = 0;
            if (val > 0) {
                if (current_product > LLONG_MAX / val) {
                    overflow = 1;
                }
            } else {
                if (current_product > 0) {
                    if (current_product > LLONG_MAX / (-val)) {
                        overflow = 1;
                    }
                } else if (current_product < 0) {
                    /* Possible weaknesses found:
                     * UBSan: division of -9223372036854775808 by -1 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000019,time:31253,execs:10946,op:havoc,rep:4)
                     */
                    if (current_product < LLONG_MIN / val) {
                        overflow = 1;
                    }
                }
            }
            
            if (overflow) {
                current_product = 1;
                continue;
            }
            
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: -1505394020450903440 * 344 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000022,time:41714,execs:14394,op:havoc,rep:2)
             */
            current_product *= val;
            
            if (total_sum > 0 && current_product > LLONG_MAX - total_sum) {
                current_product = 1;
                continue;
            }
            if (total_sum < 0 && current_product < LLONG_MIN - total_sum) {
                current_product = 1;
                continue;
            }
            
            total_sum += current_product;
        }
    }
    return total_sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000013,time:36641,execs:12655,op:havoc,rep:1; likely memory-safety defect
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