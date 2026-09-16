#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int count_unset_bits(unsigned int n) {
    int count = 0;
    while (n) {
        if (!(n & 1)) {
            count++;
        }
        n >>= 1;
    }
    return count;
}

int main(int argc, char * const * argv) {
    unsigned int num;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <unsigned_integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    unsigned long parsed = strtoul(argv[1], &endptr, 10);
    if (*endptr != '\0' || parsed > UINT_MAX) {
        fprintf(stderr, "Error: Invalid input or number out of range for unsigned int.\n");
        return EXIT_FAILURE;
    }
    num = (unsigned int)parsed;

    int result = count_unset_bits(num);
    printf("%d\n", result);
    
    return EXIT_SUCCESS;
}