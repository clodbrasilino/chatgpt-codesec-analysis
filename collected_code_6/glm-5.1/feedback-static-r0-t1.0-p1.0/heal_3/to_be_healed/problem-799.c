#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned int left_rotate_bits(unsigned int num, unsigned int d) {
    if (d == 0) {
        return num;
    }
    unsigned int bits = sizeof(num) * CHAR_BIT;
    d %= bits;
    return (num << d) | (num >> (bits - d));
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number> <rotations>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr1;
    unsigned long val1 = strtoul(argv[1], &endptr1, 10);
    if (*endptr1 != '\0' || val1 > UINT_MAX) {
        return EXIT_FAILURE;
    }

    char *endptr2;
    unsigned long val2 = strtoul(argv[2], &endptr2, 10);
    if (*endptr2 != '\0' || val2 > UINT_MAX) {
        return EXIT_FAILURE;
    }

    unsigned int num = (unsigned int)val1;
    unsigned int d = (unsigned int)val2;

    unsigned int result = left_rotate_bits(num, d);

    printf("%u\n", result);

    return EXIT_SUCCESS;
}