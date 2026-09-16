#include <stdio.h>
#include <stdlib.h>

unsigned int toggle_odd_bits(unsigned int num) {
    unsigned int mask = 0xAAAAAAAA;
    return num ^ mask;
}

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    unsigned int num;
    if (sscanf(argv[1], "%u", &num) != 1) {
        return EXIT_FAILURE;
    }

    unsigned int result = toggle_odd_bits(num);
    printf("%u\n", result);

    return EXIT_SUCCESS;
}