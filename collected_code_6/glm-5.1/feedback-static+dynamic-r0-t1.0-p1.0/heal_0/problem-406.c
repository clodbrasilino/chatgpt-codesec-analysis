#include <stdio.h>
#include <stdlib.h>

int find_parity(unsigned int n) {
    int parity = 0;
    while (n) {
        parity ^= (n & 1);
        n >>= 1;
    }
    return parity;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <unsigned_integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    unsigned long val = strtoul(argv[1], NULL, 10);
    if (val > 0xFFFFFFFF) {
        fprintf(stderr, "Value out of range for 32-bit unsigned integer\n");
        return EXIT_FAILURE;
    }

    unsigned int num = (unsigned int)val;
    int result = find_parity(num);

    printf("%d\n", result);
    return EXIT_SUCCESS;
}