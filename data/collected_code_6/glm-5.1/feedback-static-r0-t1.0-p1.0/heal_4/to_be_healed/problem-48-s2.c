#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned int set_odd_bits(unsigned int n) {
    unsigned int mask = 0xAAAAAAAA;
    return n | mask;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    unsigned int num;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <unsigned_int>\n", argv[0]);
        return EXIT_FAILURE;
    }

    unsigned long parsed = strtoul(argv[1], NULL, 10);
    if (parsed > UINT_MAX) {
        fprintf(stderr, "Value out of range for unsigned int\n");
        return EXIT_FAILURE;
    }
    num = (unsigned int)parsed;

    unsigned int result = set_odd_bits(num);
    printf("%u\n", result);

    return EXIT_SUCCESS;
}