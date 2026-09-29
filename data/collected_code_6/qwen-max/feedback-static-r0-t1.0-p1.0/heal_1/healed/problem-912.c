#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

uint64_t find_Lobb_number(uint32_t n) {
    uint64_t result = (1ULL << (2 * n)) - 1;
    return result + (n & 1);
}

int main() {
    uint32_t n;
    printf("Enter a positive integer: ");
    if (scanf("%u", &n) != 1 || n == 0) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }
    uint64_t lobb_number = find_Lobb_number(n);
    printf("Lobb number for n=%u is %" PRIu64 "\n", n, lobb_number);
    return EXIT_SUCCESS;
}