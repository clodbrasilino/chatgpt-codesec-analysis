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
                    if (total > 0) {
                        return LLONG_MAX;
                    }
                    product = 1;
                    continue;
                }
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: -460610015983834428 * 222223 cannot be represented in type 'long long' (AFL crash: id:000004,sig:06,src:000037,time:51692,execs:41751,op:quick,pos:26)
                 */
                product *= arr[j];
            } else if (arr[j] < 0) {
                if (arr[j] == -1 && product == LLONG_MIN) {
                    if (total <= 0) {
                        return LLONG_MIN;
                    }
                    product = 1;
                    continue;
                }
                if (product > 0) {
                    if (product > LLONG_MAX / (-((long long)arr[j]))) {
                        if (total <= 0) {
                            return LLONG_MIN;
                        }
                        product = 1;
                        continue;
                    }
                } else {
                    /* Possible weaknesses found:
                     * UBSan: division of -9223372036854775808 by -1 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000022,time:18342,execs:13960,op:havoc,rep:1)
                     * ASan: FPE (AFL crash: id:000001,sig:06,src:000022,time:18342,execs:13960,op:havoc,rep:1)
                     */
                    if (product < LLONG_MIN / arr[j]) {
                        if (total > 0) {
                            return LLONG_MAX;
                        }
                        product = 1;
                        continue;
                    }
                }
                product *= arr[j];
            } else {
                product = 0;
            }
            if (product > 0 && total > LLONG_MAX - product) {
                return LLONG_MAX;
            }
            if (product < 0 && total < LLONG_MIN - product) {
                return LLONG_MIN;
            }
            total += product;
        }
    }
    return total;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000021,time:17483,execs:13219,op:havoc,rep:2; likely memory-safety defect
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