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

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <unsigned_integer>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);
    if (val > UINT_MAX || *endptr != '\0') {
        fprintf(stderr, "Error: Input out of unsigned int range or invalid\n");
        return EXIT_FAILURE;
    }
    unsigned int num = (unsigned int)val;
    int result = count_unset_bits(num);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}