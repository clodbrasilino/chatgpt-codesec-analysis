#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long safe_add(long long a, long long b) {
    if ((b > 0 && a > LLONG_MAX - b) || (b < 0 && a < LLONG_MIN - b)) {
        exit(EXIT_FAILURE);
    }
    return a + b;
}

long long safe_mul(long long a, long long b) {
    if (a > 0) {
        if (b > 0) {
            if (a > LLONG_MAX / b) exit(EXIT_FAILURE);
        } else if (b < 0) {
            if (b < LLONG_MIN / a) exit(EXIT_FAILURE);
        }
    } else if (a < 0) {
        if (b > 0) {
            if (a < LLONG_MIN / b) exit(EXIT_FAILURE);
        } else if (b < 0) {
            if (a < LLONG_MAX / b) exit(EXIT_FAILURE);
        }
    }
    return a * b;
}

long long find_arithmetic_term(int n, long long a, long long d) {
    if (n <= 0) exit(EXIT_FAILURE);
    
    long long steps = n - 1;
    
    if (steps == 0) return a;
    
    long long product = safe_mul(steps, d);
    
    return safe_add(a, product);
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