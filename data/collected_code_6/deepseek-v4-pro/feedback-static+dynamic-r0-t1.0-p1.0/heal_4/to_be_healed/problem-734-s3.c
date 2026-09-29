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
            } else if (arr[j] < 0) {
                if (arr[j] == -1 && product == LLONG_MIN) {
                    if (total <= 0) {
                        return LLONG_MIN;
                    }
                    product = 1;
                    continue;
                }
                if (product > 0) {
                    if (product > LLONG_MAX / (-arr[j])) {
                        /* Possible weaknesses found:
                         * UBSan: signed integer overflow: -119326948 * 790121876544 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000027,time:54429,execs:35885,op:havoc,rep:4)
                         * UBSan: signed integer overflow: -1026405035 * 818270837136 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000019,time:42536,execs:27334,op:havoc,rep:1)
                         */
                        if ((long long)arr[j] * product < 0) {
                            if (total <= 0) {
                                return LLONG_MIN;
                            }
                            product = 1;
                            continue;
                        }
                    }
                }
            }
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: -363055079904 * 84706076 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000027,time:54433,execs:35886,op:havoc,rep:1)
             * UBSan: signed integer overflow: 818270837136 * -1026405035 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000019,time:42536,execs:27334,op:havoc,rep:1)
             * UBSan: signed integer overflow: -593599637904 * 333333313 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000030,time:42880,execs:27634,op:havoc,rep:3)
             */
            product *= arr[j];
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