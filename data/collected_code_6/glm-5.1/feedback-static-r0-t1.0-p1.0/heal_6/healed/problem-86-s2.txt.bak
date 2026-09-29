#include <stdio.h>
#include <stdlib.h>

unsigned long long centered_hexagonal(unsigned int n) {
    unsigned long long term = n;
    return 3 * term * (term - 1) + 1;
}

int main(int argc, char const * const argv[const]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    unsigned long long val = strtoull(argv[1], &endptr, 10);

    if (*endptr != '\0' || val == 0) {
        return EXIT_FAILURE;
    }

    unsigned int n = (unsigned int)val;
    printf("%llu\n", centered_hexagonal(n));

    return EXIT_SUCCESS;
}