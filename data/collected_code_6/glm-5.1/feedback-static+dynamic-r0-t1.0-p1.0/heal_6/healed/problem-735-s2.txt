#include <stdio.h>
#include <stdlib.h>

unsigned int toggle_middle_bits(unsigned int num) {
    if (num < 4) {
        return num;
    }

    unsigned int bits = sizeof(num) * 8;
    unsigned int mask = ((1U << (bits - 2)) - 1) << 1;

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