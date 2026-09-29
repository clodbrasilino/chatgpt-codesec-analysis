#include <stdio.h>
#include <stdlib.h>

long long sum_of_products(const int *arr, int n) {
    long long total = 0;
    long long current = 1;
    for (int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 5299922530323136512 * 4 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000014,time:26057,execs:16095,op:havoc,rep:1)
         * UBSan: signed integer overflow: 8609882886851625216 * 4 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000013,time:42653,execs:25993,op:havoc,rep:2)
         */
        current *= arr[i];
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 7508223586042355832 + 2752946047582994432 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000014,time:26057,execs:16095,op:havoc,rep:1)
         * UBSan: signed integer overflow: 4424523231652686614 + 8609882886851625216 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000013,time:42653,execs:25993,op:havoc,rep:2)
         */
        total += current;
    }
    return total;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
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
    long long result = sum_of_products(arr, n);
    printf("%lld\n", result);
    free(arr);
    return 0;
}