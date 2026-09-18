#include <stdio.h>
#include <stdlib.h>

long long find_sum_of_products(const int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }

    long long total_sum = 0;

    for (int i = 0; i < n; i++) {
        long long current_product = 1;
        for (int j = i; j < n; j++) {
            if (arr[j] == 0) {
                current_product = 0;
            } else {
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: 7223967240784183296 * 2 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000018,time:45600,execs:28898,op:havoc,rep:2)
                 * UBSan: signed integer overflow: 7403073866588749824 * 2 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000018,time:38901,execs:24961,op:havoc,rep:1)
                 * UBSan: signed integer overflow: 2626897178466975744 * 4 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000018,time:40180,execs:25609,op:havoc,rep:2)
                 */
                current_product *= arr[j];
            }
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 8991059068740479775 + 583754928548216832 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000018,time:39146,execs:25046,op:havoc,rep:1)
             * UBSan: signed integer overflow: 5189969478603854424 + 7403073866588749824 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000018,time:38901,execs:24961,op:havoc,rep:1)
             * UBSan: signed integer overflow: 4349432667410300748 + 7223967240784183296 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000018,time:45600,execs:28898,op:havoc,rep:2)
             */
            total_sum += current_product;
            if (current_product == 0) {
                break;
            }
        }
    }

    return total_sum;
}

int main() {
    int n;

    if (scanf("%d", &n) != 1) {
        return 1;
    }

    if (n <= 0) {
        return 0;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    
    if (arr == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return 1;
        }
    }

    long long result = find_sum_of_products(arr, n);
    printf("%lld\n", result);

    free(arr);

    return 0;
}