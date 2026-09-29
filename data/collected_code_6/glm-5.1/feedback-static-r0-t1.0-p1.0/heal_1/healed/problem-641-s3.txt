#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long nth_nonagonal(int n) {
    if (n < 1) {
        return 0;
    }
    if ((unsigned long long)n > ULLONG_MAX / 7) {
        return 0;
    }
    unsigned long long un = (unsigned long long)n;
    unsigned long long term = 7 * un;
    if (term - 5 > ULLONG_MAX - term) {
        return 0;
    }
    if ((term - 5) > ULLONG_MAX / un) {
        return 0;
    }
    unsigned long long numerator = un * (term - 5);
    return numerator / 2;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (endptr == argv[1] || *endptr != '\0' || val < 1 || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    unsigned long long result = nth_nonagonal((int)val);
    if (result == 0) {
        return EXIT_FAILURE;
    }
    printf("%llu\n", result);
    return EXIT_SUCCESS;
}