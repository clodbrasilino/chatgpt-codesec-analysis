#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

unsigned int toggle_middle_bits(unsigned int num) {
    unsigned int mask = 1U | (1U << (sizeof(num) * 8 - 1));
    mask = ~mask;
    return num ^ mask;
}

int main(int argc, char * const * argv) {
    unsigned int num = 0;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <unsigned_integer>\n", argv[0]);
        return EXIT_FAILURE;
    }
    const char *endptr = NULL;
    unsigned long val = strtoul(argv[1], (char **)&endptr, 10);
    if (*endptr != '\0' || val > __UINT32_MAX__) {
        fprintf(stderr, "Invalid input: Not a valid unsigned integer\n");
        return EXIT_FAILURE;
    }
    num = (unsigned int)val;
    unsigned int result = toggle_middle_bits(num);
    printf("%u\n", result);
    return EXIT_SUCCESS;
}