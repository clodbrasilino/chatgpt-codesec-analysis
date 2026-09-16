#include <stdio.h>
#include <stdlib.h>

unsigned int toggle_middle_bits(unsigned int num) {
    if (num < 4) {
        return num;
    }

    unsigned int high_bit_pos = 0;
    unsigned int temp = num;
    while (temp >>= 1) {
        high_bit_pos++;
    }

    unsigned int high_bit = 1U << high_bit_pos;
    unsigned int low_bit = 1U;
    unsigned int mask = high_bit - 1;
    mask ^= low_bit;

    return num ^ mask;
}

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    unsigned int num = (unsigned int)strtoul(argv[1], NULL, 10);
    unsigned int result = toggle_middle_bits(num);

    printf("%u\n", result);

    return EXIT_SUCCESS;
}