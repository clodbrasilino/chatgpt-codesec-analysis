#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int count_unset_bits(unsigned int n) {
    int count = 0;
    for (int i = 0; i < (int)(sizeof(n) * 8); i++) {
        if (!(n & 1)) {
            count++;
        }
        n >>= 1;
    }
    return count;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <unsigned_integer>\n", argv[0]);
        return EXIT_FAILURE;
    }
    unsigned long val = strtoul(argv[1], NULL, 10);
    if (val > UINT_MAX) {
        fprintf(stderr, "Error: Input out of unsigned int range\n");
        return EXIT_FAILURE;
    }
    unsigned int num = (unsigned int)val;
    int result = count_unset_bits(num);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}