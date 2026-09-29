#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

long long sum_of_products_of_subarrays(const int *arr, int n) {
    long long total = 0;
    for (int i = 0; i < n; i++) {
        long long product = 1;
        bool overflow_reset = false;
        for (int j = i; j < n; j++) {
            if (overflow_reset) {
                break;
            }
            if (arr[j] > 0) {
                if (product > LLONG_MAX / arr[j]) {
                    if (total > 0) {
                        return LLONG_MAX;
                    }
                    product = 1;
                    overflow_reset = true;
                    continue;
                }
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: -26785828366144848 * 533 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000025,time:30658,execs:24631,op:havoc,rep:2)
                 * UBSan: signed integer overflow: -5128714474871285520 * 33 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000025,time:31240,execs:25049,op:havoc,rep:1)
                 */
                product *= arr[j];
            /* Possible weaknesses found:
             *  Assuming that condition 'arr[j]<0' is not redundant
             */
            } else if (arr[j] < 0) {
                /* Possible weaknesses found:
                 *  Assignment 'abs_val=-(long long)arr[j]', assigned value is greater than 0
                 */
                long long abs_val = -(long long)arr[j];
                if (arr[j] == -1 && product == LLONG_MIN) {
                    if (total <= 0) {
                        return LLONG_MIN;
                    }
                    product = 1;
                    overflow_reset = true;
                    continue;
                }
                if (product > 0) {
                    if (product > LLONG_MAX / abs_val) {
                        if (total <= 0) {
                            return LLONG_MIN;
                        }
                        product = 1;
                        overflow_reset = true;
                        continue;
                    }
                } else {
                    /* Possible weaknesses found:
                     *  Condition 'abs_val==0' is always false [knownConditionTrueFalse]
                     *  Condition 'abs_val==0' is always false
                     */
                    if (abs_val == 0) {
                        product = 0;
                        continue;
                    }
                    /* Possible weaknesses found:
                     * ASan: FPE (AFL crash: id:000005,sig:06,src:000039,time:48799,execs:37362,op:havoc,rep:4)
                     * UBSan: division of -9223372036854775808 by -1 cannot be represented in type 'long long' (AFL crash: id:000005,sig:06,src:000039,time:48799,execs:37362,op:havoc,rep:4)
                     */
                    if (product < LLONG_MIN / arr[j]) {
                        if (total > 0) {
                            return LLONG_MAX;
                        }
                        product = 1;
                        overflow_reset = true;
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
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000011,time:24636,execs:20122,op:havoc,rep:2; likely memory-safety defect
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