#include <stdio.h>
#include <stdlib.h>

unsigned long long hexagonal_number(unsigned long long n) {
    return n * (2 * n - 1);
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    unsigned long long n = strtoull(argv[1], &endptr, 10);

    if (*endptr != '\0' || n == 0) {
        fprintf(stderr, "Error: Invalid input. n must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    if (n > 3037000499ULL) {
        fprintf(stderr, "Error: Input too large. Risk of unsigned long long overflow.\n");
        return EXIT_FAILURE;
    }

    unsigned long long result = hexagonal_number(n);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}