#include <stdio.h>
#include <stdlib.h>

long long extended_gcd(long long a, long long b, long long *x, long long *y);
int solve_equation(long long a, long long b, long long n, long long *x, long long *y);

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
    if (x == NULL || y == NULL) {
        return -1;
    }
    if (a == 0 && b == 0) {
        if (n == 0) {
            *x = 0;
            *y = 0;
            return 0;
        }
        return -1;
    }
    long long x0;
    long long y0;
    /* Possible weaknesses found:
     * UBSan: negation of -9223372036854775808 cannot be represented in type 'long long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000003,sig:06,src:000001,time:12379,execs:6427,op:havoc,rep:3)
     * UBSan: negation of -9223372036854775808 cannot be represented in type 'long long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000006,sig:06,src:000010,time:43156,execs:24425,op:havoc,rep:1)
     */
    long long g = extended_gcd(a < 0 ? -a : a, b < 0 ? -b : b, &x0, &y0);
    if (g == 0 || (n % g) != 0) {
        return -1;
    }
    long long scale = n / g;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2305843009213693952 * 7 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:1535,execs:910,op:havoc,rep:1)
     */
    *x = x0 * scale;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -4611686018427387903 * 7 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:789,execs:467,op:havoc,rep:1)
     */
    *y = y0 * scale;
    if (a < 0) {
        *x = -(*x);
    }
    if (b < 0) {
        *y = -(*y);
    }
    return 0;
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

    if (solve_equation(a, b, n, &x, &y) != 0) {
        fprintf(stderr, "No solution exists\n");
        return EXIT_FAILURE;
    }

    printf("x = %lld, y = %lld\n", x, y);
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -9223372036854775808 + -9223372036854775801 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:1535,execs:910,op:havoc,rep:1)
     * UBSan: signed integer overflow: 9223372036854775807 * 2 cannot be represented in type 'long long' (AFL crash: id:000004,sig:06,src:000010,time:26704,execs:14618,op:havoc,rep:1)
     * UBSan: signed integer overflow: 4 * 4611686018427387904 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:11750,execs:6085,op:havoc,rep:2)
     * UBSan: signed integer overflow: 9223372036854775807 * -7 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:1535,execs:910,op:havoc,rep:1)
     * UBSan: signed integer overflow: 2 * 4611686018427387911 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:789,execs:467,op:havoc,rep:1)
     * UBSan: signed integer overflow: -2 * -4611686018427387911 cannot be represented in type 'long long' (AFL crash: id:000005,sig:06,src:000008,time:39393,execs:22132,op:havoc,rep:2)
     * UBSan: signed integer overflow: -2 * 9223372036854775806 cannot be represented in type 'long long' (AFL crash: id:000004,sig:06,src:000010,time:26704,execs:14618,op:havoc,rep:1)
     * UBSan: signed integer overflow: -9223372036854775808 * -12 cannot be represented in type 'long long' (AFL crash: id:000006,sig:06,src:000010,time:43156,execs:24425,op:havoc,rep:1)
     * UBSan: signed integer overflow: 9223372036854775807 * 7 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:789,execs:467,op:havoc,rep:1)
     * UBSan: signed integer overflow: 9223372036854775807 * -2 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:11750,execs:6085,op:havoc,rep:2)
     * UBSan: signed integer overflow: 74 * 1495681951922396077 cannot be represented in type 'long long' (AFL crash: id:000006,sig:06,src:000010,time:43156,execs:24425,op:havoc,rep:1)
     */
    printf("Verification: %lld * %lld + %lld * %lld = %lld\n", a, x, b, y, a * x + b * y);

    return EXIT_SUCCESS;
}