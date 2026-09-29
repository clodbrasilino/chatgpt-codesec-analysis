#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long find_arithmetic_term(int n, long long a, long long d) {
    if (n <= 0) {
        exit(EXIT_FAILURE);
    }

    long long steps = (long long)(n - 1);

    if (d > 0) {
        if (steps > (LLONG_MAX - a) / d) {
            exit(EXIT_FAILURE);
        }
    } else if (d < 0) {
        if (d == LLONG_MIN) {
            if (steps <= -1LL) {
                exit(EXIT_FAILURE);
            }
        } else {
            if (steps < (LLONG_MIN - a) / d) {
                exit(EXIT_FAILURE);
            }
        }
    }

    return a + steps * d;
}

int main(void) {
    int n;
    long long a, d, term;

    if (scanf("%d %lld %lld", &n, &a, &d) != 3) {
        return EXIT_FAILURE;
    }

    term = find_arithmetic_term(n, a, d);

    printf("%lld\n", term);

    return EXIT_SUCCESS;
}