#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

long long power(int a, int b) {
    if (b < 0) {
        errno = EDOM;
        return 0;
    }
    if (b == 0) {
        return 1;
    }
    if (a == 0) {
        return 0;
    }

    long long result = 1;
    long long base = a;
    int exp = b;

    if (base < 0) {
        base = -base;
    }

    while (exp > 0) {
        if (exp % 2 == 1) {
            if (result > LLONG_MAX / base) {
                errno = ERANGE;
                return 0;
            }
            result *= base;
        }
        exp /= 2;
        if (exp > 0) {
            if (base > LLONG_MAX / base) {
                errno = ERANGE;
                return 0;
            }
            base *= base;
        }
    }

    if (a < 0 && b % 2 != 0) {
        result = -result;
    }

    return result;
}

int main(int argc, char * const * argv) {
    if (argc != 3) {
        return EXIT_FAILURE;
    }

    char *endptr_a;
    char *endptr_b;
    errno = 0;
    long val_a = strtol(argv[1], &endptr_a, 10);
    long val_b = strtol(argv[2], &endptr_b, 10);

    if (errno == ERANGE || endptr_a == argv[1] || *endptr_a != '\0' || val_a < INT_MIN || val_a > INT_MAX) {
        return EXIT_FAILURE;
    }

    if (errno == ERANGE || endptr_b == argv[2] || *endptr_b != '\0' || val_b < INT_MIN || val_b > INT_MAX) {
        return EXIT_FAILURE;
    }

    errno = 0;
    long long res = power((int)val_a, (int)val_b);

    if (errno != 0) {
        return EXIT_FAILURE;
    }

    printf("%lld\n", res);

    return EXIT_SUCCESS;
}