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

int main(int argc, char * const argv[const]) {
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