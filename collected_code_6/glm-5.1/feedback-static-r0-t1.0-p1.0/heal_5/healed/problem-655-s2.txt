#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long sum_of_fifth_powers(unsigned int n) {
    unsigned long long sum = 0;
    for (unsigned int i = 1; i <= n; ++i) {
        unsigned long long term = (unsigned long long)i * i * i * i * i;
        if (sum > ULLONG_MAX - term) {
            fprintf(stderr, "Overflow detected\n");
            exit(EXIT_FAILURE);
        }
        sum += term;
    }
    return sum;
}

int main(int argc, char * const argv[]) {
    unsigned int n;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);
    if (*endptr != '\0' || val > UINT_MAX) {
        fprintf(stderr, "Invalid input. Provide a valid natural number.\n");
        return EXIT_FAILURE;
    }
    n = (unsigned int)val;
    unsigned long long result = sum_of_fifth_powers(n);
    printf("%llu\n", result);
    return EXIT_SUCCESS;
}