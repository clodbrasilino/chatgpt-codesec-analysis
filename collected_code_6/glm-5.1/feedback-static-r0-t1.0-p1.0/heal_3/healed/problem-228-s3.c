#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int all_bits_unset(unsigned int num, unsigned int l, unsigned int r) {
    if (l < 1 || r < 1 || l > r || l > sizeof(num) * CHAR_BIT || r > sizeof(num) * CHAR_BIT) {
        return 0;
    }
    unsigned int range_length = r - l + 1;
    unsigned int mask = (range_length == sizeof(num) * CHAR_BIT) ? ~0u : ((1u << range_length) - 1);
    mask <<= (l - 1);
    if ((num & mask) == 0) {
        return 1;
    }
    return 0;
}

int main(int argc, char * const argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <number> <l> <r>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);
    if (*endptr != '\0') {
        return EXIT_FAILURE;
    }
    unsigned long l_val = strtoul(argv[2], &endptr, 10);
    if (*endptr != '\0') {
        return EXIT_FAILURE;
    }
    unsigned long r_val = strtoul(argv[3], &endptr, 10);
    if (*endptr != '\0') {
        return EXIT_FAILURE;
    }
    if (val > 0xFFFFFFFF || l_val > 0xFFFFFFFF || r_val > 0xFFFFFFFF) {
        return EXIT_FAILURE;
    }
    unsigned int num = (unsigned int)val;
    unsigned int l = (unsigned int)l_val;
    unsigned int r = (unsigned int)r_val;
    int result = all_bits_unset(num, l, r);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}