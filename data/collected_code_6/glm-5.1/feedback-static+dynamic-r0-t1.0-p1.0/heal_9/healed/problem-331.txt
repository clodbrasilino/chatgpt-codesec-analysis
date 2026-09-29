#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

int count_unset_bits(unsigned int n) {
    int count = 0;
    while (n) {
        count += !(n & 1);
        n >>= 1;
    }
    return count;
}

int main(int argc, char * const * argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);
    if (*endptr != '\0' || val > UINT_MAX) {
        fprintf(stderr, "Invalid input or out of range\n");
        return EXIT_FAILURE;
    }
    unsigned int num = (unsigned int)val;
    int unset_bits = count_unset_bits(num);
    printf("%d\n", unset_bits);
    return EXIT_SUCCESS;
}