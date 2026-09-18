#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long find_arithmetic_term(int n, long long a, long long d) {
    if (n <= 0) {
        exit(EXIT_FAILURE);
    }

    long long steps = (long long)(n - 1);

    if (d > 0) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223372036854775807 - -1111 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000004,time:700,execs:456,op:quick,pos:7)
         */
        if (steps > (LLONG_MAX - a) / d) {
            exit(EXIT_FAILURE);
        }
    } else if (d < 0) {
        if (d == LLONG_MIN) {
            if (steps <= -1LL) {
                exit(EXIT_FAILURE);
            }
        } else {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: -9223372036854775808 - 1 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:1255,execs:792,op:havoc,rep:3)
             */
            if (steps < (LLONG_MIN - a) / d) {
                exit(EXIT_FAILURE);
            }
        }
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -9223372036854775808 + -7770 cannot be represented in type 'long long' (AFL crash: id:000004,sig:06,src:000007,time:34922,execs:20353,op:havoc,rep:1)
     * UBSan: signed integer overflow: -9223372036854775808 + -6029737926045683564 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000005,time:11246,execs:6845,op:havoc,rep:27)
     * UBSan: signed integer overflow: 440576676 * -55555555555 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000005,time:11246,execs:6845,op:havoc,rep:27)
     * UBSan: signed integer overflow: 110 * -9223372036854775808 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000004,time:11732,execs:7124,op:havoc,rep:3)
     */
    return a + steps * d;
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