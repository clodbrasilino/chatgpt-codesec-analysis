#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long find_arithmetic_term(int n, long long a, long long d) {
    if (n <= 0) {
        exit(EXIT_FAILURE);
    }

    if (a == LLONG_MIN && d == -1) {
        exit(EXIT_FAILURE);
    }

    long long steps = (long long)(n - 1);

    if (steps > 0) {
        if (d > 0) {
            if (a > 0 && steps > (LLONG_MAX - a) / d) {
                exit(EXIT_FAILURE);
            }
            if (a < 0 && steps > (LLONG_MAX + a) / d) {
                exit(EXIT_FAILURE);
            }
        } else if (d < 0) {
            if (d == LLONG_MIN) {
                exit(EXIT_FAILURE);
            }
            if (a > 0) {
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: 51111111511 - -9223372036854775808 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000004,time:1230,execs:622,op:havoc,rep:4)
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

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -9223372036854775808 + -16790734427653710 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000010,time:38590,execs:17424,op:havoc,rep:7)
     * UBSan: signed integer overflow: 1111110 * -1111111111111116 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000008,time:12052,execs:5794,op:havoc,rep:7)
     */
    return a + steps * d;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000002,sig:06,src:000009,time:27940,execs:12930,op:havoc,rep:9; likely memory-safety defect
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