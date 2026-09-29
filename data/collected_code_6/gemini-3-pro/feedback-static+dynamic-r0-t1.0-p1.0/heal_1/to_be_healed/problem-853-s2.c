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
    long long i = 3;
    
    while (i * i <= n) {
        long long current_sum = 1;
        long long current_term = 1;
        while (n % i == 0) {
            current_term *= i;
            current_sum += current_term;
            n /= i;
        }
        sum *= current_sum;
        i += 2;
    }

    if (n > 1) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 16923530597376 * 649658 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:364,execs:210,op:havoc,rep:5)
         */
        sum *= (1 + n);
    }

    return sum;
}

int main(void) {
    long long n;
    
    if (scanf("%lld", &n) != 1) {
        return EXIT_FAILURE;
    }

    long long result = sum_of_odd_factors(n);
    printf("%lld\n", result);

    return EXIT_SUCCESS;
}