#include <stdio.h>
#include <stdlib.h>

long long gcd_extended(long long a, long long b, long long *x, long long *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }
    long long x1, y1;
    long long gcd = gcd_extended(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return gcd;
}

int find_solution(long long a, long long b, long long n, long long *x, long long *y) {
    if (a == 0 && b == 0) {
        if (n == 0) {
            *x = 0;
            *y = 0;
            return 1;
        }
        return 0;
    }
    if (a == 0) {
        if (n % b != 0) return 0;
        *x = 0;
        *y = n / b;
        return 1;
    }
    if (b == 0) {
        if (n % a != 0) return 0;
        *x = n / a;
        *y = 0;
        return 1;
    }

    long long x_g, y_g;
    /* Possible weaknesses found:
     * UBSan: negation of -9223372036854775808 cannot be represented in type 'long long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000003,sig:06,src:000011,time:37441,execs:18420,op:havoc,rep:2)
     * UBSan: negation of -9223372036854775808 cannot be represented in type 'long long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000004,sig:06,src:000015,time:43701,execs:21351,op:havoc,rep:6)
     */
    long long g = gcd_extended(llabs(a), llabs(b), &x_g, &y_g);

    if (n % g != 0) {
        return 0;
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2305843009213693952 * 7 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:853,execs:450,op:havoc,rep:1)
     */
    *x = x_g * (n / g);
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -4611686018427387903 * 7 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:1014,execs:533,op:havoc,rep:1)
     * UBSan: signed integer overflow: -216 * 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000007,time:26213,execs:12895,op:havoc,rep:3)
     */
    *y = y_g * (n / g);

    if (a < 0) *x = -(*x);
    if (b < 0) *y = -(*y);

    return 1;
}

int main(void) {
    long long a, b, n, x, y;

    if (scanf("%lld %lld %lld", &a, &b, &n) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (find_solution(a, b, n, &x, &y)) {
        printf("%lld %lld\n", x, y);
    } else {
        printf("No solution\n");
    }

    return EXIT_SUCCESS;
}