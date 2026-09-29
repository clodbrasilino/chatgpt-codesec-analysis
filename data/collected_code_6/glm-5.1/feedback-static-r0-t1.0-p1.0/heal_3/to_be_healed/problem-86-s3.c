#include <stdio.h>
#include <stdlib.h>

unsigned long long centered_hexagonal(unsigned int n) {
    return 1ULL + (unsigned long long)n * (n - 1) * 3;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);

    if (*endptr != '\0' || val == 0) {
        fprintf(stderr, "Invalid input. n must be a positive integer.\n");
        return 1;
    }

    unsigned int n = (unsigned int)val;
    unsigned long long result = centered_hexagonal(n);

    printf("%llu\n", result);
    return 0;
}