#include <stdio.h>
#include <stdlib.h>

static long long extended_gcd(long long a, long long b, long long *x, long long *y)
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

static int solve_equation(long long a, long long b, long long n, long long *x, long long *y)
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
    long long g = extended_gcd(llabs(a), llabs(b), &x0, &y0);
    if (g == 0 || n % g != 0) {
        return -1;
    }
    long long factor = n / g;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2305843009213693952 * 7 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:1941,execs:1155,op:havoc,rep:1)
     */
    *x = x0 * factor;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -4611686018427387903 * 7 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:1926,execs:1148,op:havoc,rep:1)
     * UBSan: signed integer overflow: -4611686018427387903 * 2444 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000001,time:15812,execs:8469,op:havoc,rep:4)
     */
    *y = y0 * factor;
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
        printf("No integer solution exists for %lldx + %lldy = %lld\n", a, b, n);
        return EXIT_FAILURE;
    }

    printf("Solution: x = %lld, y = %lld\n", x, y);
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 * 2 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:11240,execs:6264,op:havoc,rep:4)
     * UBSan: signed integer overflow: 2 * 4611686018427387911 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:1926,execs:1148,op:havoc,rep:1)
     * UBSan: signed integer overflow: 9223372036854775807 * 2 cannot be represented in type 'long long' (AFL crash: id:000004,sig:06,src:000001,time:53108,execs:29957,op:havoc,rep:4)
     * UBSan: signed integer overflow: -2 * 9223372036854775806 cannot be represented in type 'long long' (AFL crash: id:000004,sig:06,src:000001,time:53108,execs:29957,op:havoc,rep:4)
     * UBSan: signed integer overflow: 4 * -4611686018427387904 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:11240,execs:6264,op:havoc,rep:4)
     * UBSan: signed integer overflow: 9223372036854775807 * -7 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:1941,execs:1155,op:havoc,rep:1)
     * UBSan: signed integer overflow: 9223372036854775807 * 2444 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000001,time:15812,execs:8469,op:havoc,rep:4)
     * UBSan: signed integer overflow: -9223372036854775808 + -9223372036854775801 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:1941,execs:1155,op:havoc,rep:1)
     * UBSan: signed integer overflow: 9223372036854775807 * 7 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:1926,execs:1148,op:havoc,rep:1)
     */
    printf("Check: %lld * %lld + %lld * %lld = %lld\n", a, x, b, y, a * x + b * y);
    return EXIT_SUCCESS;
}