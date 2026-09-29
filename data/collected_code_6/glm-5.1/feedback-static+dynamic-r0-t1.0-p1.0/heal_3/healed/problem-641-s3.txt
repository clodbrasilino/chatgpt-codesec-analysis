#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long nth_nonagonal(int n) {
    if (n < 1) {
        return 0;
    }
    unsigned long long un = (unsigned long long)n;
    if (un > ULLONG_MAX / 7) {
        return 0;
    }
    unsigned long long term = 7 * un;
    if (term < 5) {
        return 0;
    }
    unsigned long long diff = term - 5;
    if (un > ULLONG_MAX / diff) {
        return 0;
    }
    unsigned long long product = un * diff;
    return product / 2;
}

int main(int argc, char * const * argv) {
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