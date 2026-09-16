#include <stdio.h>
#include <stdlib.h>

unsigned int set_odd_bits(unsigned int n) {
    unsigned int mask = 0;
    mask = ~mask;
    mask = mask & 0xAAAAAAAA;
    return n | mask;
}

int main(int argc, char *argv[]) {
    unsigned int num;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <unsigned_integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (sscanf(argv[1], "%u", &num) != 1) {
        fprintf(stderr, "Invalid input: Not a valid unsigned integer.\n");
        return EXIT_FAILURE;
    }

    num = set_odd_bits(num);

    printf("%u\n", num);

    return EXIT_SUCCESS;
}