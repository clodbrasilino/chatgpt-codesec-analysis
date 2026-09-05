#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long calculate_sum_of_cubes(unsigned int n) {
    unsigned long long sum = 0;
    for (unsigned int i = 1; i <= n; i++) {
        sum += (unsigned long long)i * i * i;
    }
    return sum;
}

int main(int argc, char * const * const argv) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);
    
    if (*endptr != '\0' || val > UINT_MAX) {
        return EXIT_FAILURE;
    }

    unsigned int n = (unsigned int)val;
    if (n == 0) {
        return EXIT_FAILURE;
    }

    unsigned long long result = calculate_sum_of_cubes(n);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}