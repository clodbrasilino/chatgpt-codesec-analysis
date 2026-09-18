#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int power(long long base, unsigned int exp, long long *result)
{
    long long acc = 1;
    long long b = base;
    unsigned int e = exp;

    if (result == NULL) {
        return -1;
    }

    while (e > 0U) {
        if ((e & 1U) == 1U) {
            /* Possible weaknesses found:
             * UBSan: negation of -9223372036854775808 cannot be represented in type 'long long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000001,sig:06,src:000022,time:46370,execs:27714,op:havoc,rep:5)
             */
            if (b != 0 && (acc > LLONG_MAX / (b > 0 ? b : -b) ||
                           acc < LLONG_MIN / (b > 0 ? b : -b))) {
                return -1;
            }
            acc *= b;
        }
        e >>= 1U;
        if (e > 0U) {
            /* Possible weaknesses found:
             * UBSan: negation of -9223372036854775808 cannot be represented in type 'long long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000000,sig:06,src:000022,time:44998,execs:26883,op:havoc,rep:7)
             */
            if (b != 0 && ((b > 0 ? b : -b) > LLONG_MAX / (b > 0 ? b : -b))) {
                return -1;
            }
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: -9223372036854775808 * -9223372036854775808 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000022,time:44998,execs:26883,op:havoc,rep:7)
             */
            b *= b;
        }
    }

    *result = acc;
    return 0;
}

int main(void)
{
    long long a;
    unsigned int b;
    long long result;
    int ret;

    printf("Enter base (integer): ");
    if (scanf("%lld", &a) != 1) {
        fprintf(stderr, "Invalid input for base\n");
        return EXIT_FAILURE;
    }

    printf("Enter exponent (non-negative integer): ");
    if (scanf("%u", &b) != 1) {
        fprintf(stderr, "Invalid input for exponent\n");
        return EXIT_FAILURE;
    }

    ret = power(a, b, &result);
    if (ret != 0) {
        fprintf(stderr, "Error: overflow or invalid arguments\n");
        return EXIT_FAILURE;
    }

    printf("%lld^%u = %lld\n", a, b, result);
    return EXIT_SUCCESS;
}