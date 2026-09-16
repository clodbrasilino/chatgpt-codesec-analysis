#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned int toggle_even_bits(unsigned int num) {
    unsigned int mask = 0x55555555;
    return num ^ mask;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);

    if (*endptr != '\0' || val > UINT_MAX) {
        return EXIT_FAILURE;
    }

    unsigned int num = (unsigned int)val;
    unsigned int result = toggle_even_bits(num);

    printf("%u\n", result);

    return EXIT_SUCCESS;
}