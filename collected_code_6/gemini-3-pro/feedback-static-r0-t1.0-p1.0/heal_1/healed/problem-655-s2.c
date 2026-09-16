#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

unsigned long long sum_of_fifth_powers(unsigned int n) {
    unsigned long long sum = 0;
    for (unsigned int i = 1; i <= n; i++) {
        unsigned long long i_ull = (unsigned long long)i;
        unsigned long long power = i_ull * i_ull * i_ull * i_ull * i_ull;
        
        if (ULLONG_MAX - sum < power) {
            fprintf(stderr, "Error: Integer overflow occurred during calculation.\n");
            exit(EXIT_FAILURE);
        }
        sum += power;
    }
    return sum;
}

int main(int argc, char *const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive_integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);

    if (errno != 0 || *endptr != '\0' || val <= 0 || val > UINT_MAX) {
        fprintf(stderr, "Error: Please provide a valid positive integer.\n");
        return EXIT_FAILURE;
    }

    unsigned int n = (unsigned int)val;
    unsigned long long result = sum_of_fifth_powers(n);

    printf("%llu\n", result);

    return EXIT_SUCCESS;
}