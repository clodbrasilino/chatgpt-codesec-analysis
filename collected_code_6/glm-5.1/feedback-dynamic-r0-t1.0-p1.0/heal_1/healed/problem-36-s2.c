#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_nth_digit(long long numerator, long long denominator, long long n) {
    if (denominator == 0 || n <= 0) {
        return -1;
    }

    if (numerator < 0) {
        numerator = -numerator;
    }
    if (denominator < 0) {
        denominator = -denominator;
    }

    numerator = numerator % denominator;

    for (long long i = 0; i < n; i++) {
        if (numerator > LLONG_MAX / 10) {
            return -1;
        }
        numerator *= 10;
        if (numerator == 0 && i > 0) {
            return 0;
        }
    }

    int digit = (int)((numerator / denominator) % 10);

    return digit;
}

int main(void) {
    long long num, den, n;

    if (scanf("%lld %lld %lld", &num, &den, &n) != 3) {
        return EXIT_FAILURE;
    }

    int result = find_nth_digit(num, den, n);

    printf("%d\n", result);

    return EXIT_SUCCESS;
}