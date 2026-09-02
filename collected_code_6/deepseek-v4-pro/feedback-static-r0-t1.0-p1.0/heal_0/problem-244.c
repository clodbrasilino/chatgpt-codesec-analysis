#include <stdio.h>
#include <math.h>
#include <limits.h>

long long next_perfect_square(long long n) {
    if (n < 0) {
        return 0;
    }
    if (n >= LLONG_MAX) {
        return LLONG_MAX;
    }

    long long root = (long long)sqrt((double)n);
    if (root * root <= n) {
        root++;
    } else {
        while (root > 0 && root * root > n) {
            root--;
        }
        if (root * root <= n) {
            root++;
        }
    }

    if (root > (long long)sqrt((double)LLONG_MAX)) {
        return LLONG_MAX;
    }

    return root * root;
}

int main(void) {
    long long test_values[] = {0, 1, 2, 9, 10, 16, 17, 100, 101, 999999999999999999LL};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);

    for (size_t i = 0; i < num_tests; i++) {
        printf("next_perfect_square(%lld) = %lld\n", test_values[i], next_perfect_square(test_values[i]));
    }

    return 0;
}