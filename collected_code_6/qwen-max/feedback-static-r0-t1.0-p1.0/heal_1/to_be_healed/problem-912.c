#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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
    /* Possible weaknesses found:
     *  %llu in format string (no. 2) requires 'unsigned long long' but the argument type is 'unsigned long'. [invalidPrintfArgType_uint]
     */
    printf("Lobb number for n=%u is %llu\n", n, lobb_number);
    return EXIT_SUCCESS;
}