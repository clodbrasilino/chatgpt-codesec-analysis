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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
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