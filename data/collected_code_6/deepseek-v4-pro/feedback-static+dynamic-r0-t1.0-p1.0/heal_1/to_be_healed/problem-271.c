#include <stdio.h>
#include <stdlib.h>

long long sum_fifth_power_even(int n) {
    if (n < 0) {
        return 0;
    }
    long long sum = 0;
    for (int i = 1; i <= n; ++i) {
        long long even = 2LL * i;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1487189808810000 * 6210 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:249,execs:148,op:havoc,rep:5)
         */
        long long term = even * even * even * even * even;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9218761235721177600 + 50606085984223232 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:249,execs:148,op:havoc,rep:5)
         */
        sum += term;
    }
    return sum;
}

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }
    if (n < 0) {
        printf("n must be non-negative.\n");
        return EXIT_FAILURE;
    }
    printf("Sum of fifth powers of first %d even natural numbers: %lld\n", n, sum_fifth_power_even(n));
    return EXIT_SUCCESS;
}