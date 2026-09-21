#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <errno.h>

uint64_t carol_number(int n) {
    if (n < 1) {
        exit(EXIT_FAILURE);
    }
    
    int shift = n + 1;
    
    if (shift >= 64) {
        exit(EXIT_FAILURE);
    }
    
    uint64_t power_of_two = (uint64_t)1 << shift;
    uint64_t two_n_minus_one = power_of_two - 1;
    uint64_t result = two_n_minus_one * two_n_minus_one - 2;
    
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr;
    errno = 0;
    long n = strtol(argv[1], &endptr, 10);
    
    if (errno != 0 || *endptr != '\0' || n < 1 || n > INT_MAX) {
        fprintf(stderr, "n must be a positive integer\n");
        return EXIT_FAILURE;
    }
    
    uint64_t res = carol_number((int)n);
    printf("%llu\n", (unsigned long long)res);
    
    return EXIT_SUCCESS;
}