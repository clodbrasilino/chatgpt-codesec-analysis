#include <stdio.h>
#include <stdlib.h>

unsigned int set_odd_bits(unsigned int n) {
    return n | 0x55555555;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);
    if (*endptr != '\0' || val > 0xFFFFFFFF) {
        return EXIT_FAILURE;
    }

    unsigned int num = (unsigned int)val;
    unsigned int result = set_odd_bits(num);

    printf("%u\n", result);

    return EXIT_SUCCESS;
}