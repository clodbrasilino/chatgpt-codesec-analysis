#include <stdio.h>
#include <stdlib.h>

unsigned long long calc_nonagonal_number(unsigned int n) {
    if (n == 0) {
        return 0;
    }
    return (unsigned long long)n * (7ULL * n - 5ULL) / 2ULL;
}

int main(int argc, const char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long long input = strtoll(argv[1], &endptr, 10);

    if (*endptr != '\0' || input < 0 || input > 1000000000) {
        fprintf(stderr, "Invalid input. Please provide a positive integer.\n");
        return EXIT_FAILURE;
    }

    unsigned int n = (unsigned int)input;
    unsigned long long result = calc_nonagonal_number(n);

    printf("%llu\n", result);

    return EXIT_SUCCESS;
}