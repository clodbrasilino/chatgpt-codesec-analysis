#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

unsigned int set_odd_bits(unsigned int n) {
    unsigned int mask = 0xAAAAAAAA;
    return n | mask;
}

int main(int argc, char * const argv[const]) {
    unsigned int num;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <unsigned_int>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    unsigned long parsed = strtoul(argv[1], &endptr, 10);
    
    if (errno != 0 || *endptr != '\0' || parsed > UINT_MAX) {
        fprintf(stderr, "Invalid input or value out of range for unsigned int\n");
        return EXIT_FAILURE;
    }
    num = (unsigned int)parsed;

    unsigned int result = set_odd_bits(num);
    printf("%u\n", result);

    return EXIT_SUCCESS;
}