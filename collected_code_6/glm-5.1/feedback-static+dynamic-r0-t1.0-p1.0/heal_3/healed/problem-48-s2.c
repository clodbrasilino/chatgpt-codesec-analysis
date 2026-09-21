#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

unsigned int set_odd_bits(unsigned int n) {
    return n | 0x55555555U;
}

int main(int argc, char * const * argv) {
    unsigned int num;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <unsigned_int>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *endptr;
    unsigned long parsed = strtoul(argv[1], &endptr, 10);

    if (errno == ERANGE || parsed > UINT_MAX || *endptr != '\0') {
        fprintf(stderr, "Invalid input or value out of range for unsigned int\n");
        return EXIT_FAILURE;
    }

    num = (unsigned int)parsed;

    unsigned int result = set_odd_bits(num);
    printf("%u\n", result);

    return EXIT_SUCCESS;
}