#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long find_arithmetic_term(int n, long long a, long long d) {
    if (n <= 0) {
        exit(EXIT_FAILURE);
    }

    long long steps = (long long)(n - 1);

    if (steps > 0) {
        if (d > 0) {
            if (steps > (LLONG_MAX - a) / d) {
                exit(EXIT_FAILURE);
            }
        } else if (d < 0) {
            if (d == LLONG_MIN) {
                exit(EXIT_FAILURE);
            }
            if (a > 0) {
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: 4 - -9223372036854775808 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000004,time:41893,execs:16448,op:havoc,rep:56)
                 */
                if (steps > (a - LLONG_MIN) / -d) {
                    exit(EXIT_FAILURE);
                }
            } else {
                if (steps < (LLONG_MIN - a) / d) {
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    return a + steps * d;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:878,execs:334,op:havoc,rep:1; likely memory-safety defect
  */

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