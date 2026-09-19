#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
long long sum_of_products_of_subarrays(int *arr, int n) {
    long long total = 0;
    for (int i = 0; i < n; i++) {
        long long product = 1;
        for (int j = i; j < n; j++) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 616101502505651580 * 422 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000012,time:8943,execs:5275,op:havoc,rep:5)
             */
            product *= arr[j];
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 2085695714463565584 + 8342585325407348736 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000009,time:11548,execs:6759,op:havoc,rep:4)
             */
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