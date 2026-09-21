#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

long long find_nth_digit(long long numerator, long long denominator, long long n) {
    if (denominator == 0 || n <= 0) {
        return -1;
    }
    if (numerator < 0) {
        numerator = -numerator;
    }
    if (denominator < 0) {
        denominator = -denominator;
    }
    long long remainder = numerator % denominator;
    for (long long i = 0; i < n; ++i) {
        remainder *= 10;
        int digit = (int)(remainder / denominator);
        remainder %= denominator;
        if (i == n - 1) {
            return digit;
        }
    }
    return -1;
}

int main(int argc, char * const * argv) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <numerator> <denominator> <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    errno = 0;
    long long numerator = strtoll(argv[1], &endptr, 10);
    if (errno != 0 || *endptr != '\0') {
        return EXIT_FAILURE;
    }
    errno = 0;
    long long denominator = strtoll(argv[2], &endptr, 10);
    if (errno != 0 || *endptr != '\0') {
        return EXIT_FAILURE;
    }
    errno = 0;
    long long n = strtoll(argv[3], &endptr, 10);
    if (errno != 0 || *endptr != '\0') {
        return EXIT_FAILURE;
    }
    if (numerator == LLONG_MIN || denominator == LLONG_MIN || n == LLONG_MIN) {
        return EXIT_FAILURE;
    }
    long long result = find_nth_digit(numerator, denominator, n);
    if (result == -1) {
        return EXIT_FAILURE;
    }
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}