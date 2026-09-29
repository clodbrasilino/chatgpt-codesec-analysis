#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_nth_digit(long long numerator, long long denominator, int n) {
    if (denominator == 0 || n <= 0) {
        return -1;
    }

    if (numerator < 0) {
        numerator = -(unsigned long long)numerator;
    }
    if (denominator < 0) {
        denominator = -(unsigned long long)denominator;
    }

    unsigned long long unum = (unsigned long long)(numerator % denominator);

    for (int i = 0; i < n; i++) {
        if (unum > ULLONG_MAX / 10) {
            unsigned long long q = unum / denominator;
            unsigned long long r = unum % denominator;
            unum = (q % 10) * (ULLONG_MAX / 10) * 10;
            unum += (q / 10) * (ULLONG_MAX / 10);
            unum += r * 10;
        } else {
            unum *= 10;
        }
        if (unum == 0 && i > 0) {
            return 0;
        }
    }

    int digit = (int)((unum / denominator) % 10);

    return digit;
}

int main(void) {
    long long num, den;
    int n;

    if (scanf("%lld %lld %d", &num, &den, &n) != 3) {
        return EXIT_FAILURE;
    }

    int result = find_nth_digit(num, den, n);

    printf("%d\n", result);

    return EXIT_SUCCESS;
}