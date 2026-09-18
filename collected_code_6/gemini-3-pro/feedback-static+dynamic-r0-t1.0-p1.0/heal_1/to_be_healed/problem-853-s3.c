#include <stdio.h>
#include <stdlib.h>

long long sum_of_odd_factors(long long n) {
    if (n < 0) {
        n = -n;
    }
    
    if (n == 0) {
        return 0;
    }

    while (n % 2 == 0) {
        n /= 2;
    }

    long long sum = 1;
    for (long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            long long term = 1;
            long long current_sum = 1;
            while (n % i == 0) {
                term *= i;
                current_sum += term;
                n /= i;
            }
            sum *= current_sum;
        }
    }

    if (n > 2) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 16923530597376 * 649658 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000003,time:557,execs:272,op:havoc,rep:1)
         */
        sum *= (1 + n);
    }

    return sum;
}

int main(void) {
    long long n;
    int result = scanf("%lld", &n);
    
    if (result != 1) {
        return EXIT_FAILURE;
    }

    long long sum = sum_of_odd_factors(n);
    printf("%lld\n", sum);

    return EXIT_SUCCESS;
}