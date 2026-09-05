#include <stdio.h>
#include <stdlib.h>

unsigned int toggle_middle_bits(unsigned int num) {
    if (sizeof(num) * 8 <= 2) {
        return num;
    }

    unsigned int mask = 0;
    mask = ~mask;
    mask = mask << 1;
    mask = mask >> 1;
    mask = mask >> 1;
    mask = mask << 1;
    mask = ~mask;

    return num ^ mask;
}

int main(int argc, char *argv[]) {
    unsigned int num = 0;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <unsigned_integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr = NULL;
    unsigned long val = strtoul(argv[1], &endptr, 10);

    if (*endptr != '\0' || val > __UINT32_MAX__) {
        fprintf(stderr, "Invalid input: Not a valid unsigned integer\n");
        return EXIT_FAILURE;
    }

    num = (unsigned int)val;

    unsigned int result = toggle_middle_bits(num);

    printf("%u\n", result);

    return EXIT_SUCCESS;
}