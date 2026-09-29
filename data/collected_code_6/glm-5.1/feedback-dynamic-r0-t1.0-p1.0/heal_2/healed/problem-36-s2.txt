#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_nth_digit(long long numerator, long long denominator, long long n) {
    if (denominator == 0 || n <= 0) {
        return -1;
    }

    if (numerator < 0) {
        numerator = -(unsigned long long)numerator;
    }
    if (denominator < 0) {
        denominator = -(unsigned long long)denominator;
    }

    numerator = numerator % denominator;

    if (numerator == 0) {
        return 0;
    }

    for (long long i = 0; i < n; i++) {
        if (numerator > LLONG_MAX / 10) {
            return -1;
        }
        numerator *= 10;
        if (numerator >= denominator) {
            if (i == n - 1) {
                return (int)((numerator / denominator) % 10);
            }
            numerator %= denominator;
            if (numerator == 0) {
                return 0;
            }
        }
    }

    return 0;
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