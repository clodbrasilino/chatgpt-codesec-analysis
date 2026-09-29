#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long sum_of_products_of_subarrays(const int *arr, int n) {
    long long total = 0;
    for (int i = 0; i < n; i++) {
        long long product = 1;
        for (int j = i; j < n; j++) {
            if (arr[j] > 0) {
                if (product > LLONG_MAX / arr[j]) {
                    total = LLONG_MAX;
                    return total;
                }
            } else if (arr[j] < 0) {
                /* Possible weaknesses found:
                 * ASan: FPE (AFL crash: id:000001,sig:06,src:000010,time:15762,execs:5342,op:havoc,rep:5)
                 * UBSan: division of -9223372036854775808 by -1 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000010,time:15762,execs:5342,op:havoc,rep:5)
                 */
                if (product < LLONG_MIN / arr[j]) {
                    total = LLONG_MIN;
                    return total;
                }
            }
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 20008000800 * -598358244 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000010,time:42036,execs:14886,op:havoc,rep:5)
             */
            product *= arr[j];
            if (product > 0 && total > LLONG_MAX - product) {
                total = LLONG_MAX;
                return total;
            }
            if (product < 0 && total < LLONG_MIN - product) {
                total = LLONG_MIN;
                return total;
            }
            total += product;
        }
    }
    return total;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:9061,execs:3109,op:havoc,rep:1; likely memory-safety defect
  */

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }
    int *arr = (int *)malloc((size_t)n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return 1;
        }
    }
    long long result = sum_of_products_of_subarrays(arr, n);
    printf("%lld\n", result);
    free(arr);
    return 0;
}