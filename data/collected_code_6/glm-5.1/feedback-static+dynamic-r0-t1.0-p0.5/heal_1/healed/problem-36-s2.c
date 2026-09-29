#include <stdio.h>
#include <stdlib.h>

int find_nth_digit(int numerator, int denominator, int n) {
    if (denominator == 0 || n <= 0) {
        return -1;
    }

    long long num = (long long)numerator;
    long long den = (long long)denominator;

    if (num < 0) num = -num;
    if (den < 0) den = -den;

    num = num % den;

    for (int i = 0; i < n; i++) {
        num *= 10;
        if (i == n - 1) {
            return (int)(num / den);
        }
        num = num % den;
    }

    return -1;
}

int main(int argc, char * const argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <numerator> <denominator> <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0') return EXIT_FAILURE;
    int numerator = (int)val;

    val = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' || val == 0) return EXIT_FAILURE;
    int denominator = (int)val;

    val = strtol(argv[3], &endptr, 10);
    if (*endptr != '\0' || val <= 0) return EXIT_FAILURE;
    int n = (int)val;

    int result = find_nth_digit(numerator, denominator, n);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}