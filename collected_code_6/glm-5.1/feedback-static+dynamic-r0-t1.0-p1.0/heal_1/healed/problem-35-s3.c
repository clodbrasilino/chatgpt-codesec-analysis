#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long find_nth_rectangular_number(unsigned int n) {
    unsigned long long term = n;
    return term * (term + 1);
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    unsigned long long val = strtoull(argv[1], &endptr, 10);

    if (*endptr != '\0' || val == 0) {
        return EXIT_FAILURE;
    }

    if (val > UINT_MAX) {
        return EXIT_FAILURE;
    }

    unsigned int n = (unsigned int)val;
    unsigned long long result = find_nth_rectangular_number(n);

    printf("%llu\n", result);

    return EXIT_SUCCESS;
}