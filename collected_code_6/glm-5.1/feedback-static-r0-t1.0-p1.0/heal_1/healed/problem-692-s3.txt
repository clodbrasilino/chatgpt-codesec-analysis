#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int last_two_digits_factorial(int n) {
    if (n < 0) {
        return -1;
    }
    if (n >= 10) {
        return 0;
    }
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
        result %= 100;
    }
    return (int)result;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val > INT_MAX || val < INT_MIN) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    int n = (int)val;
    int res = last_two_digits_factorial(n);
    if (res == -1) {
        fprintf(stderr, "Factorial is not defined for negative numbers\n");
        return EXIT_FAILURE;
    }
    printf("%02d\n", res);
    return EXIT_SUCCESS;
}