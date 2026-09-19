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
                 * UBSan: signed integer overflow: -3412760023713506324 * 2222 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000029,time:44178,execs:32314,op:havoc,rep:1)
                 * UBSan: signed integer overflow: -2884030282257184060 * 222222214 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000025,time:34367,execs:26095,op:havoc,rep:3)
                 * UBSan: signed integer overflow: -11965830716 * 2124130190 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000025,time:31637,execs:24188,op:havoc,rep:1)
                 * UBSan: signed integer overflow: -16442486302 * 622222222 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000025,time:30526,execs:23492,op:havoc,rep:5)
                 * UBSan: signed integer overflow: -1177144210501531756 * 24 cannot be represented in type 'long long' (AFL crash: id:000004,sig:06,src:000029,time:44251,execs:32358,op:havoc,rep:1)
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
                if (product < 0) {
                    if (product == LLONG_MIN || (-product) > LLONG_MAX / abs_val) {
                        if (total > 0) {
                            return LLONG_MAX;
                        }
                        product = 1;
                        overflow_reset = true;
                        continue;
                    }
                } else {
                    if (product > LLONG_MAX / abs_val) {
                        if (total <= 0) {
                            return LLONG_MIN;
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