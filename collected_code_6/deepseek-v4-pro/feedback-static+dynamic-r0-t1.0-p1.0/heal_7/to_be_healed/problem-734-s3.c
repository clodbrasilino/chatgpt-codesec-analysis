#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

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
                 * UBSan: signed integer overflow: -1213362681254567580 * 4444 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000041,time:38596,execs:30861,op:havoc,rep:1)
                 * UBSan: signed integer overflow: -4973857853050659628 * 2 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000019,time:17513,execs:15157,op:havoc,rep:2)
                 * UBSan: signed integer overflow: -2512534646767464 * 846706949 cannot be represented in type 'long long' (AFL crash: id:000004,sig:06,src:000041,time:40668,execs:32191,op:havoc,rep:1)
                 * UBSan: signed integer overflow: -15992600852712 * 44444411 cannot be represented in type 'long long' (AFL crash: id:000006,sig:06,src:000041,time:44220,execs:34263,op:havoc,rep:2)
                 * UBSan: signed integer overflow: -4619739939145959888 * 2 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000041,time:37074,execs:29860,op:havoc,rep:2)
                 * UBSan: signed integer overflow: -664276445712 * 747507931 cannot be represented in type 'long long' (AFL crash: id:000007,sig:06,src:000041,time:48934,execs:36912,op:havoc,rep:4)
                 * UBSan: signed integer overflow: -286391211348 * 44444411 cannot be represented in type 'long long' (AFL crash: id:000005,sig:06,src:000041,time:42263,execs:33105,op:havoc,rep:1)
                 * UBSan: signed integer overflow: -67418822628 * 244444411 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000041,time:38265,execs:30654,op:havoc,rep:4)
                 */
                product *= arr[j];
            } else if (arr[j] < 0) {
                if (arr[j] == LLONG_MIN || (arr[j] == -1 && product == LLONG_MIN)) {
                    if (total <= 0) {
                        return LLONG_MIN;
                    }
                    product = 1;
                    overflow_reset = true;
                    continue;
                }
                long long abs_val = (arr[j] == LLONG_MIN) ? LLONG_MAX : -(long long)arr[j];
                if (abs_val == 0) {
                    product = 0;
                    continue;
                }
                /* Possible weaknesses found:
                 *  Assuming that condition 'product>0' is not redundant
                 */
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
                     *  Condition 'product>0' is always false [knownConditionTrueFalse]
                     *  Condition 'product>0' is always false
                     */
                    if (product > 0) {
                        if (abs_val > LLONG_MAX / product) {
                            if (total <= 0) {
                                return LLONG_MIN;
                            }
                            product = 1;
                            overflow_reset = true;
                            continue;
                        }
                    } else {
                        if (product == LLONG_MIN || (arr[j] != 0 && (product < 0 ? (-product) > LLONG_MAX / (-(long long)arr[j]) : false))) {
                            if (total > 0) {
                                return LLONG_MAX;
                            }
                            product = 1;
                            overflow_reset = true;
                            continue;
                        }
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