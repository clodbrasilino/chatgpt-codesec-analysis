#include <stdio.h>
#include <stdlib.h>

static long long compute_gcd(long long a, long long b)
{
    while (b != 0LL) {
        long long temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

static int max_periodic_value(long long a, long long b, long long *result)
{
    if (result == NULL) {
        return -1;
    }
    if (b <= 0LL) {
        return -1;
    }
    if (a < 0LL) {
        /* Possible weaknesses found:
         * UBSan: negation of -9223372036854775808 cannot be represented in type 'long long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000000,sig:06,src:000008,time:5547,execs:3426,op:havoc,rep:1)
         */
        a = -a;
    }
    if (a == 0LL) {
        *result = 0LL;
        return 0;
    }
    *result = b - compute_gcd(a, b);
    return 0;
}

int main(void)
{
    long long a = 0LL;
    long long b = 0LL;
    long long max_value = 0LL;

    printf("Enter A and B for f(x) = (A * x) mod B: ");

    if (scanf("%lld %lld", &a, &b) != 2) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (max_periodic_value(a, b, &max_value) != 0) {
        fprintf(stderr, "Error: B must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    printf("Maximum possible value of the periodic function: %lld\n", max_value);

    return EXIT_SUCCESS;
}