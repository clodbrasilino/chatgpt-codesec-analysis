#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

uint64_t hamming_distance(uint64_t a, uint64_t b) {
    uint64_t x = a ^ b;
    uint64_t count = 0;
    while (x) {
        count += x & 1;
        x >>= 1;
    }
    return count;
}

uint64_t total_hamming_distance(uint64_t n) {
    if (n == 0) {
        return 0;
    }
    uint64_t sum = 0;
    for (uint64_t i = 0; i < n; i++) {
        sum += hamming_distance(i, i + 1);
    }
    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr = NULL;
    uint64_t n = strtoull(argv[1], &endptr, 10);

    if (*endptr != '\0' || n == 0) {
        return EXIT_FAILURE;
    }

    uint64_t result = total_hamming_distance(n);
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%" PRIu64 "\n", result);
    fputs(buffer, stdout);

    return EXIT_SUCCESS;
}