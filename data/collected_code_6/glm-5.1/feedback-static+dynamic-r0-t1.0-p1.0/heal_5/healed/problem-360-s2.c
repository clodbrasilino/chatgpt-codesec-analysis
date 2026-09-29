#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

uint64_t find_nth_carol(int n) {
    if (n <= 0 || n >= 32) {
        return 0;
    }
    uint64_t m = 1ULL << (n + 1);
    return (m - 1) * (m - 1) - 2;
}

int main(int argc, char * const * argv) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    char *endptr;
    long n = strtol(argv[1], &endptr, 10);
    if (endptr == argv[1] || *endptr != '\0' || n <= 0 || n >= 32 || n > INT_MAX) {
        return EXIT_FAILURE;
    }
    uint64_t result = find_nth_carol((int)n);
    printf("%llu\n", (unsigned long long)result);
    return EXIT_SUCCESS;
}