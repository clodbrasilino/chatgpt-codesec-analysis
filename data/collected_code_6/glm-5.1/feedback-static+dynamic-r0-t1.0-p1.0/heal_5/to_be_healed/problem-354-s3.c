#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long find_arithmetic_term(int n, long long a, long long d) {
    if (n <= 0) {
        exit(EXIT_FAILURE);
    }

    if (d == LLONG_MIN) {
        exit(EXIT_FAILURE);
    }

    if (a == LLONG_MIN && d < 0) {
        exit(EXIT_FAILURE);
    }

    long long steps = (long long)(n - 1);

    if (steps > 0) {
        long long abs_d = (d > 0) ? d : -d;

        if (d > 0) {
            if (a > 0 && abs_d > (LLONG_MAX - a) / steps) {
                exit(EXIT_FAILURE);
            }
            if (a < 0 && abs_d > (LLONG_MAX + a) / steps) {
                exit(EXIT_FAILURE);
            }
        } else if (d < 0) {
            long long abs_a = (a > 0) ? a : -a;
            
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 5 - -9223372036854775808 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000005,time:2362,execs:1205,op:havoc,rep:4)
             */
            if (a > 0 && abs_d > (abs_a - LLONG_MIN) / steps) {
                exit(EXIT_FAILURE);
            }
            if (a < 0 && abs_d > (LLONG_MIN - a) / steps) {
                exit(EXIT_FAILURE);
            }
        }
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 50 * 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000007,time:7949,execs:3631,op:havoc,rep:2)
     * UBSan: signed integer overflow: 30 * -2222222222222211111 cannot be represented in type 'long long' (AFL crash: id:000005,sig:06,src:000011,time:50375,execs:22894,op:quick,pos:24)
     */
    long long product = steps * d;
    
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -9223372036854775808 - 3333323 cannot be represented in type 'long long' (AFL crash: id:000004,sig:06,src:000008,time:24603,execs:11318,op:havoc,rep:8)
     * UBSan: signed integer overflow: 9223372036854775807 - -111111111 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000004,time:17824,execs:8190,op:havoc,rep:1)
     * UBSan: signed integer overflow: 9223372036854775807 - -5 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:9694,execs:4418,op:havoc,rep:1)
     */
    if ((d > 0 && product > LLONG_MAX - a) || (d < 0 && product < LLONG_MIN - a)) {
        exit(EXIT_FAILURE);
    }

    return a + product;
}

int main(void) {
    int n;
    long long a, d, term;

    if (scanf("%d %lld %lld", &n, &a, &d) != 3) {
        return EXIT_FAILURE;
    }

    term = find_arithmetic_term(n, a, d);

    printf("%lld\n", term);

    return EXIT_SUCCESS;
}