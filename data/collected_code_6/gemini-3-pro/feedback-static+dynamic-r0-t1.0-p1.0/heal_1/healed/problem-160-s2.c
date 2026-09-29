#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

__int128_t gcd_extended(__int128_t a, __int128_t b, __int128_t *x, __int128_t *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }

    __int128_t x1, y1;
    __int128_t gcd = gcd_extended(b % a, a, &x1, &y1);

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

    __int128_t a128 = a;
    __int128_t b128 = b;
    __int128_t n128 = n;
    
    __int128_t abs_a = a128 < 0 ? -a128 : a128;
    __int128_t abs_b = b128 < 0 ? -b128 : b128;

    __int128_t x0, y0;
    __int128_t g = gcd_extended(abs_a, abs_b, &x0, &y0);

    if (g == 0 || n128 % g != 0) {
        return false;
    }

    __int128_t res_x = x0 * (n128 / g);
    __int128_t res_y = y0 * (n128 / g);

    if (a128 < 0) res_x = -res_x;
    if (b128 < 0) res_y = -res_y;

    long long max_ll = 9223372036854775807LL;
    long long min_ll = -max_ll - 1;

    if (res_x < min_ll || res_x > max_ll || res_y < min_ll || res_y > max_ll) {
        return false;
    }

    *x = (long long)res_x;
    *y = (long long)res_y;

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