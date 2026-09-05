#include <stdio.h>
#include <stdlib.h>

unsigned int toggle_middle_bits(unsigned int num) {
    if (num < 4) {
        return num;
    }

    unsigned int mask = 0xFFFFFFFF;
    unsigned int bits = (unsigned int)sizeof(num) * 8;

    mask = (mask >> 1) << 1;
    mask = mask >> (bits - 2);
    mask = mask << 1;

    return num ^ mask;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    unsigned int num = (unsigned int)strtoul(argv[1], NULL, 10);
    unsigned int result = toggle_middle_bits(num);

    printf("%u\n", result);

    return EXIT_SUCCESS;
}