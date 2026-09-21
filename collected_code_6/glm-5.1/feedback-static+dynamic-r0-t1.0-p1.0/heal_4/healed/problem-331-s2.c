#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int count_unset_bits(unsigned int n) {
    int count = 0;
    unsigned int temp = n;
    while (temp) {
        count += !(temp & 1);
        temp >>= 1;
    }
    return count;
}

int main(int argc, char const * const argv[const]) {
    unsigned int num;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <unsigned_integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    unsigned long parsed = strtoul(argv[1], &endptr, 10);

    if (errno != 0 || *endptr != '\0' || parsed > UINT_MAX) {
        fprintf(stderr, "Error: Invalid input or number out of range for unsigned int.\n");
        return EXIT_FAILURE;
    }
    num = (unsigned int)parsed;

    int result = count_unset_bits(num);
    printf("%d\n", result);
    
    return EXIT_SUCCESS;
}