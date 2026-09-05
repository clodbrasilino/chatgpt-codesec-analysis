#include <stdio.h>
#include <stdlib.h>

unsigned int set_even_bits(unsigned int n) {
    unsigned int mask = 0x55555555;
    return n | mask;
}

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        return 1;
    }
    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);
    if (*endptr != '\0' || val > 0xFFFFFFFFU) {
        return 1;
    }
    unsigned int num = (unsigned int)val;
    unsigned int result = set_even_bits(num);
    printf("%u\n", result);
    return 0;
}