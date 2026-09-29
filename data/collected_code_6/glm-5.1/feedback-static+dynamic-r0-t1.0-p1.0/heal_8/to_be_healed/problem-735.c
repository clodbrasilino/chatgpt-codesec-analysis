#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 12, got 4294967284
  *  test case 2 failed: expected 13, got 4294967285
  *  test case 0 failed: expected 15, got 4294967285
  */

unsigned int toggle_middle_bits(unsigned int num) {
    if (sizeof(num) * 8 <= 2) {
        return num;
    }

    unsigned int mask = ~0U;
    mask ^= (1U << (sizeof(num) * 8 - 1));
    mask ^= 1U;

    unsigned int middle_bits = (num >> 1) ^ mask;
    middle_bits &= mask;

    return (num & 1U) | (num & (1U << (sizeof(num) * 8 - 1))) | (middle_bits << 1);
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