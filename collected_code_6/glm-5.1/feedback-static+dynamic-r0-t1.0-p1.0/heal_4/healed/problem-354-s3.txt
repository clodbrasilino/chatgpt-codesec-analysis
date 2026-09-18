#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long find_arithmetic_term(int n, long long a, long long d) {
    if (n <= 0) {
        exit(EXIT_FAILURE);
    }

    if (d == LLONG_MIN) {
        exit(EXIT_FAILURE);
    }

    if (a == LLONG_MIN && d < 0) {
        exit(EXIT_FAILURE);
    }

    long long steps = (long long)(n - 1);

    if (steps > 0) {
        long long abs_d = (d > 0) ? d : -d;

        if (d > 0) {
            if (a > 0 && abs_d > (LLONG_MAX - a) / steps) {
                exit(EXIT_FAILURE);
            }
            if (a < 0 && abs_d > (LLONG_MAX + a) / steps) {
                exit(EXIT_FAILURE);
            }
        } else if (d < 0) {
            long long abs_a = (a > 0) ? a : -a;
            
            if (a > 0 && abs_d > (abs_a - LLONG_MIN) / steps) {
                exit(EXIT_FAILURE);
            }
            if (a < 0 && abs_d > (LLONG_MIN - a) / steps) {
                exit(EXIT_FAILURE);
            }
        }
    }

    long long product = steps * d;
    
    if ((d > 0 && product > LLONG_MAX - a) || (d < 0 && product < LLONG_MIN - a)) {
        exit(EXIT_FAILURE);
    }

    return a + product;
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