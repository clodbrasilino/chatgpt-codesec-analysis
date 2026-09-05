#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

unsigned long long sum_of_fourth_powers(int n) {
    unsigned long long sum = 0;
    for (int i = 1; i <= n; i++) {
        unsigned long long term = (unsigned long long)i * i * i * i;
        if (sum > ULLONG_MAX - term) {
            errno = ERANGE;
            return 0;
        }
        sum += term;
    }
    return sum;
}

int main(int argc, char * const * argv) {
    int n;
    char *endptr;
    unsigned long long result;

    if (argc != 2) {
        return EXIT_FAILURE;
    }

    errno = 0;
    long val = strtol(argv[1], &endptr, 10);
    if (errno != 0 || endptr == argv[1] || *endptr != '\0' || val < 1 || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    n = (int)val;

    result = sum_of_fourth_powers(n);
    if (errno == ERANGE) {
        return EXIT_FAILURE;
    }

    printf("%llu\n", result);
    return EXIT_SUCCESS;
}