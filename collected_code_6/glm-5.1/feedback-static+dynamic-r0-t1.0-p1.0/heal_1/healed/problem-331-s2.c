#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int count_unset_bits(unsigned int n) {
    int count = 0;
    unsigned int temp = n;
    while (temp) {
        if ((temp & 1) == 0) {
            count++;
        }
        temp >>= 1;
    }
    return count;
}

int main(int argc, char * const argv[]) {
    unsigned int num;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <unsigned_integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    unsigned long parsed = strtoul(argv[1], NULL, 10);
    if (parsed > UINT_MAX) {
        fprintf(stderr, "Error: Number out of range for unsigned int.\n");
        return EXIT_FAILURE;
    }
    num = (unsigned int)parsed;

    int result = count_unset_bits(num);
    printf("%d\n", result);
    
    return EXIT_SUCCESS;
}