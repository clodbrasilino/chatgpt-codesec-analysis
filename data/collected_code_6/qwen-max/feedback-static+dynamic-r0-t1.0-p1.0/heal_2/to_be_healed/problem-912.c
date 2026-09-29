#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t find_Lobb_number(uint32_t n) {
    /* Possible weaknesses found:
     *  Assuming that condition 'n>32' is not redundant
     */
    if (n > 32) {
        return 0;
    }
    /* Possible weaknesses found:
     * UBSan: shift exponent 64 is too large for 64-bit type 'unsigned long long' (AFL crash: id:000000,sig:06,src:000001,time:50045,execs:40562,op:havoc,rep:7)
     *  Shift
     *  Shifting 64-bit value by 64 bits is undefined behaviour. See condition at line 6. [shiftTooManyBits]
     */
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
    printf("Lobb number for n=%u is %llu\n", n, (unsigned long long)lobb_number);
    return EXIT_SUCCESS;
}