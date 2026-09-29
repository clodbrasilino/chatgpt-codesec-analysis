#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 13, got <no output>
  *  test case 0 failed: expected 15, got <no output>
  *  test case 1 failed: expected 12, got <no output>
  */

unsigned int toggle_middle_bits(unsigned int num) {
    if (num < 4) {
        return num;
    }

    unsigned int bits = sizeof(num) * 8;
    unsigned int mask = ((1U << (bits - 2)) - 1) << 1;

    return num ^ mask;
}

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    unsigned int num = (unsigned int)strtoul(argv[1], NULL, 10);
    unsigned int result = toggle_middle_bits(num);

    printf("%u\n", result);

    return EXIT_SUCCESS;
}