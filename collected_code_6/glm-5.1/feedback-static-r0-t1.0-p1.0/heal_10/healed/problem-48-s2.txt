#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned int set_odd_bits(unsigned int n) {
    unsigned int mask = 0xAAAAAAAA;
    return n | mask;
}

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