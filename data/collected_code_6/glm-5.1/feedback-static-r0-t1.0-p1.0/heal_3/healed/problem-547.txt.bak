#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

uint64_t hamming_distance(uint64_t a, uint64_t b) {
    uint64_t x = a ^ b;
    x = x - ((x >> 1) & UINT64_C(0x5555555555555555));
    x = (x & UINT64_C(0x3333333333333333)) + ((x >> 2) & UINT64_C(0x3333333333333333));
    x = (x + (x >> 4)) & UINT64_C(0x0F0F0F0F0F0F0F0F);
    return (x * UINT64_C(0x0101010101010101)) >> 56;
}

uint64_t total_hamming_distance(uint64_t n) {
    uint64_t sum = 0;
    for (uint64_t i = 0; i < n; i++) {
        sum += hamming_distance(i, i + 1);
    }
    return sum;
}

int main(int argc, char * const * argv) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr = NULL;
    uint64_t n = strtoull(argv[1], &endptr, 10);

    if (*endptr != '\0') {
        return EXIT_FAILURE;
    }

    uint64_t result = total_hamming_distance(n);
    printf("%" PRIu64 "\n", result);

    return EXIT_SUCCESS;
}