#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned int set_odd_bits(unsigned int n) {
    unsigned int mask = 0;
    for (int i = 1; i < sizeof(unsigned int) * 8; i += 2) {
        mask |= (1U << i);
    }
    return n | mask;
}

int main(int argc, char * const argv[]) {
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