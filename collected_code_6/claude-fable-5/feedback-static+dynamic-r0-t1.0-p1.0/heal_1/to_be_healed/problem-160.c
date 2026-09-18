#include <stdio.h>
#include <stdlib.h>

long long extended_gcd(long long a, long long b, long long *x, long long *y)
{
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    long long x1;
    long long y1;
    long long g = extended_gcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return g;
}

int solve_equation(long long a, long long b, long long n, long long *x, long long *y)
{
    if (a == 0 && b == 0) {
        if (n == 0) {
            *x = 0;
            *y = 0;
            return 1;
        }
        return 0;
    }
    /* Possible weaknesses found:
     * UBSan: negation of -9223372036854775808 cannot be represented in type 'long long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000003,sig:06,src:000007,time:55857,execs:33301,op:havoc,rep:3)
     * UBSan: negation of -9223372036854775808 cannot be represented in type 'long long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000004,sig:06,src:000007,time:58729,execs:35118,op:havoc,rep:1)
     */
    long long g = extended_gcd(a < 0 ? -a : a, b < 0 ? -b : b, x, y);
    if (n % g != 0) {
        return 0;
    }
    long long factor = n / g;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2305843009213693952 * 7 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:3104,execs:1568,op:havoc,rep:1)
     */
    *x *= factor;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -4611686018427387903 * 7 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:1219,execs:675,op:havoc,rep:1)
     * UBSan: signed integer overflow: -3074457345618258602 * 7 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000006,time:27648,execs:15965,op:havoc,rep:2)
     */
    *y *= factor;
    if (a < 0) {
        *x = -(*x);
    }
    if (b < 0) {
        *y = -(*y);
    }
    return 1;
}

int main(void)
{
    long long a;
    long long b;
    long long n;
    long long x;
    long long y;

    printf("Enter a, b, n: ");
    if (scanf("%lld %lld %lld", &a, &b, &n) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (solve_equation(a, b, n, &x, &y)) {
        printf("x = %lld, y = %lld\n", x, y);
    } else {
        printf("No solution exists\n");
    }

    return EXIT_SUCCESS;
}