#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>

static int64_t extended_gcd_ll(int64_t a, int64_t b, int64_t *x, int64_t *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    int64_t x1, y1;
    int64_t gcd = extended_gcd_ll(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return gcd;
}

static bool mul_overflows_ll(int64_t a, int64_t b, int64_t *result) {
#if defined(__GNUC__) || defined(__clang__)
    return __builtin_mul_overflow(a, b, result);
#else
    if (a == 0 || b == 0) {
        *result = 0;
        return false;
    }
    if (a > 0) {
        if (b > 0) {
            if (a > INT64_MAX / b) return true;
        } else {
            if (b < INT64_MIN / a) return true;
        }
    } else {
        if (b > 0) {
            if (a < INT64_MIN / b) return true;
        } else {
            if (a < INT64_MAX / b) return true;
        }
    }
    *result = a * b;
    return false;
#endif
}

int find_solution(int a, int b, int n, int *x, int *y) {
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

    int64_t a64 = a;
    int64_t b64 = b;
    int64_t n64 = n;
    int64_t abs_a = (a64 < 0) ? -a64 : a64;
    int64_t abs_b = (b64 < 0) ? -b64 : b64;

    int64_t x64, y64;
    int64_t gcd = extended_gcd_ll(abs_a, abs_b, &x64, &y64);

    if (n64 % gcd != 0) {
        return -1;
    }

    int64_t factor = n64 / gcd;
    if (a64 < 0) x64 = -x64;
    if (b64 < 0) y64 = -y64;

    if (mul_overflows_ll(x64, factor, &x64) || mul_overflows_ll(y64, factor, &y64)) {
        return -1;
    }

    if (x64 < INT_MIN || x64 > INT_MAX || y64 < INT_MIN || y64 > INT_MAX) {
        return -1;
    }

    *x = (int)x64;
    *y = (int)y64;
    return 0;
}

int main(void) {
    int a, b, n, x, y;

    printf("Enter coefficients a, b and value n: ");
    if (scanf("%d %d %d", &a, &b, &n) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (find_solution(a, b, n, &x, &y) == 0) {
        printf("Solution: x = %d, y = %d\n", x, y);
    } else {
        printf("No solution exists\n");
    }

    return EXIT_SUCCESS;
}