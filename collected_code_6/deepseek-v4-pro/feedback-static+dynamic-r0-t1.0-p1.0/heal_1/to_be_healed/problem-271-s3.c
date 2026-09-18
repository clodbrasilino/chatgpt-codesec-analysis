#include <stdio.h>
#include <stdlib.h>

long long sum_fifth_power_even(int n) {
    if (n <= 0) {
        return 0;
    }
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        long long even = 2LL * i;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9218761235721177600 + 50606085984223232 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:740,execs:402,op:havoc,rep:1)
         * UBSan: signed integer overflow: 4398046511104 * 2097152 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:740,execs:402,op:havoc,rep:1)
         * UBSan: signed integer overflow: 1487189808810000 * 6210 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:740,execs:402,op:havoc,rep:1)
         * UBSan: signed integer overflow: 167375247831000 * 55110 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:740,execs:402,op:havoc,rep:1)
         */
        sum += even * even * even * even * even;
    }
    return sum;
}

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (n < 0) {
        fprintf(stderr, "n must be non-negative\n");
        return EXIT_FAILURE;
    }
    printf("Sum of fifth powers of first %d even natural numbers: %lld\n", n, sum_fifth_power_even(n));
    return EXIT_SUCCESS;
}