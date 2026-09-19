#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
long long sum_of_products_subarrays(int arr[], int n) {
    long long total_sum = 0;
    for (int i = 0; i < n; i++) {
        long long product = 1;
        for (int j = i; j < n; j++) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 7970851473359634432 * 4 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000014,time:42771,execs:24659,op:havoc,rep:2)
             * UBSan: signed integer overflow: 3438406517919842304 * 3 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000014,time:27603,execs:16039,op:havoc,rep:1)
             */
            product *= arr[j];
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 2742007445325173872 + 7970851473359634432 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000014,time:42771,execs:24659,op:havoc,rep:2)
             * UBSan: signed integer overflow: 2713143093040469104 + 7757596332004474880 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000014,time:27603,execs:16039,op:havoc,rep:1)
             */
            total_sum += product;
        }
    }
    return total_sum;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    if (n <= 0) {
        return 0;
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

    long long result = sum_of_products_subarrays(arr, n);
    printf("%lld\n", result);

    free(arr);
    return 0;
}