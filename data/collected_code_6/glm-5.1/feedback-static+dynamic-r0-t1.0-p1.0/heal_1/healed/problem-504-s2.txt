#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long cube_sum(unsigned int n) {
    unsigned long long sum = 0;
    for (unsigned int i = 1; i <= n; i++) {
        unsigned long long cube = (unsigned long long)i * i * i;
        if (sum > ULLONG_MAX - cube) {
            return 0;
        }
        sum += cube;
    }
    return sum;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);
    if (*endptr != '\0' || val > UINT_MAX) {
        return EXIT_FAILURE;
    }

    unsigned long long result = cube_sum((unsigned int)val);
    if (result == 0 && val > 0) {
        return EXIT_FAILURE;
    }

    printf("%llu\n", result);
    return EXIT_SUCCESS;
}