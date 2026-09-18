#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef __int128_t int128;

int128 gcd_extended(int128 a, int128 b, int128 *x, int128 *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }
    int128 x1, y1;
    int128 gcd = gcd_extended(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return gcd;
}

int find_solution(long long a_in, long long b_in, long long n_in, long long *x_out, long long *y_out) {
    int128 a = a_in;
    int128 b = b_in;
    int128 n = n_in;

    if (a == 0 && b == 0) {
        if (n == 0) {
            *x_out = 0;
            *y_out = 0;
            return 1;
        }
        return 0;
    }
    
    if (a == 0) {
        if (n % b != 0) return 0;
        int128 curr_y = n / b;
        if (curr_y > LLONG_MAX || curr_y < LLONG_MIN) return 0;
        *x_out = 0;
        *y_out = (long long)curr_y;
        return 1;
    }
    
    if (b == 0) {
        if (n % a != 0) return 0;
        int128 curr_x = n / a;
        if (curr_x > LLONG_MAX || curr_x < LLONG_MIN) return 0;
        *x_out = (long long)curr_x;
        *y_out = 0;
        return 1;
    }

    int128 abs_a = a < 0 ? -a : a;
    int128 abs_b = b < 0 ? -b : b;
    int128 x_g, y_g;
    
    int128 g = gcd_extended(abs_a, abs_b, &x_g, &y_g);

    if (n % g != 0) {
        return 0;
    }

    int128 final_x = x_g * (n / g);
    int128 final_y = y_g * (n / g);

    if (a < 0) final_x = -final_x;
    if (b < 0) final_y = -final_y;

    if (final_x > LLONG_MAX || final_x < LLONG_MIN) return 0;
    if (final_y > LLONG_MAX || final_y < LLONG_MIN) return 0;

    *x_out = (long long)final_x;
    *y_out = (long long)final_y;

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