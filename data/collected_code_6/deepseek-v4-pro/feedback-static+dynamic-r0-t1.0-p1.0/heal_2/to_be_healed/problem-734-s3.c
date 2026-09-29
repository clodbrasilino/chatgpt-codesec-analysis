#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long sum_of_products_of_subarrays(const int *arr, int n) {
    long long total = 0;
    for (int i = 0; i < n; i++) {
        long long product = 1;
        for (int j = i; j < n; j++) {
            if (product > LLONG_MAX / arr[j] || product < LLONG_MIN / arr[j]) {
                if (arr[j] < 0) {
                    if (product < 0 && product < LLONG_MIN / arr[j]) {
                        /* Possible weaknesses found:
                         *  Value stored to 'product' is never read [deadcode.DeadStores]
                         *  Variable 'product' is assigned a value that is never used. [unreadVariable]
                         */
                        product = LLONG_MIN;
                        total = LLONG_MIN;
                        return total;
                    }
                } else {
                    /* Possible weaknesses found:
                     *  Value stored to 'product' is never read [deadcode.DeadStores]
                     *  Variable 'product' is assigned a value that is never used. [unreadVariable]
                     */
                    product = LLONG_MAX;
                    total = LLONG_MAX;
                    return total;
                }
            }
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 15785126832 * -598358244 cannot be represented in type 'long long' (AFL crash: id:000004,sig:06,src:000011,time:35144,execs:11248,op:havoc,rep:1)
             */
            product *= arr[j];
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 9223372036854775807 - -16 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000008,time:7244,execs:2449,op:havoc,rep:1)
             */
            if ((arr[j] > 0 && total > LLONG_MAX - product) ||
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: -9223372036854775808 - 9001583301196748608 cannot be represented in type 'long long' (AFL crash: id:000004,sig:06,src:000011,time:35144,execs:11248,op:havoc,rep:1)
                 */
                (arr[j] < 0 && total < LLONG_MIN - product)) {
                if (product > 0) {
                    total = LLONG_MAX;
                } else {
                    total = LLONG_MIN;
                }
                return total;
            }
            total += product;
        }
    }
    return total;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000008,time:6871,execs:2326,op:havoc,rep:2; likely memory-safety defect
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