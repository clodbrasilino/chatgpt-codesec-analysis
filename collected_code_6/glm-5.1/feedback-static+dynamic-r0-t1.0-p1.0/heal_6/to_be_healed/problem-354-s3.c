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
             * UBSan: signed integer overflow: 6 + 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000002,time:985,execs:437,op:havoc,rep:1)
             */
            if (a > 0 && abs_d > (abs_a + LLONG_MAX) / steps) {
                exit(EXIT_FAILURE);
            }
            if (a < 0 && abs_d > (LLONG_MIN - a) / steps) {
                exit(EXIT_FAILURE);
            }
        }
    }

    long long product;
    if (steps > 0) {
        if (d > 0) {
            if (d > LLONG_MAX / steps) {
                exit(EXIT_FAILURE);
            }
        } else {
            if (d < LLONG_MIN / steps) {
                exit(EXIT_FAILURE);
            }
        }
        product = steps * d;
    } else {
        product = 0;
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 - -6 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:368,execs:177,op:havoc,rep:1)
     */
    if ((product > 0 && product > LLONG_MAX - a) || (product < 0 && product < LLONG_MIN - a)) {
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