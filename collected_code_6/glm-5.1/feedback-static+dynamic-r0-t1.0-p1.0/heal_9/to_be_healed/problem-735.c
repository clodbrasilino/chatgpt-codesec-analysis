#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 15, got 9
  *  test case 2 failed: expected 13, got 11
  *  test case 1 failed: expected 12, got 10
  */

unsigned int toggle_middle_bits(unsigned int num) {
    if (sizeof(num) * 8 <= 2) {
        return num;
    }

    unsigned int mask = (~0U >> 1);
    mask <<= 1;
    mask ^= 1U;
    mask = ~mask;

    unsigned int middle_bits = num ^ mask;

    return middle_bits;
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