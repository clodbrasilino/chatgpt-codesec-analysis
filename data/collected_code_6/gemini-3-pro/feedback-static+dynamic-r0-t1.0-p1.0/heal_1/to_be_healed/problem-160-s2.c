#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

bool find_solution(long long a, long long b, long long n, long long *x, long long *y) {
    if (a == 0 && b == 0) {
        if (n == 0) {
            *x = 0;
            *y = 0;
            return true;
        }
        return false;
    }

    long long x0, y0;
    long long g = gcd_extended(abs(a), abs(b), &x0, &y0);

    /* Possible weaknesses found:
     * UBSan: division by zero (AFL crash: id:000003,sig:06,src:000014,time:46386,execs:24761,op:havoc,rep:1)
     */
    if (n % g != 0) {
        return false;
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 204871361 * 3444444444444444444 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000009,time:21439,execs:11097,op:havoc,rep:2)
     * ASan: FPE (AFL crash: id:000003,sig:06,src:000014,time:46386,execs:24761,op:havoc,rep:1)
     * UBSan: signed integer overflow: -15358179 * 1111111111111 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:12188,execs:6214,op:havoc,rep:2)
     */
    *x = x0 * (n / g);
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -170492847 * 3444444444444444444 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000009,time:21439,execs:11097,op:havoc,rep:2)
     * UBSan: signed integer overflow: -193 * 244444444444444447 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000014,time:31005,execs:16364,op:havoc,rep:5)
     */
    *y = y0 * (n / g);

    if (a < 0) *x = -*x;
    if (b < 0) *y = -*y;

    return true;
}

int main(void) {
    long long a, b, n;
    long long x, y;

    if (scanf("%lld %lld %lld", &a, &b, &n) != 3) {
        return EXIT_FAILURE;
    }

    if (find_solution(a, b, n, &x, &y)) {
        printf("x = %lld, y = %lld\n", x, y);
    } else {
        printf("No solution exists.\n");
    }

    return EXIT_SUCCESS;
}