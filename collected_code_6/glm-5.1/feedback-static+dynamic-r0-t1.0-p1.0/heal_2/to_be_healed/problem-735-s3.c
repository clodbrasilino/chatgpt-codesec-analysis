#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 12, got 4294967284
  *  test case 2 failed: expected 13, got 4294967285
  *  test case 0 failed: expected 15, got 4294967287
  */

unsigned int toggle_middle_bits(unsigned int num) {
    if (num <= 1) {
        return num;
    }
    unsigned int mask = ~0U;
    int leading_zeros = 0;
    unsigned int tmp = num;
    while (!(tmp & (~0U >> 1))) {
        leading_zeros++;
        tmp <<= 1;
    }
    unsigned int msb_mask = ~0U << (sizeof(unsigned int) * 8 - 1);
    mask = (mask >> (leading_zeros + 1)) << 1;
    mask |= msb_mask;
    return num ^ mask;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return 1;
    }
    char *endptr;
    unsigned int num = strtoul(argv[1], &endptr, 10);
    if (*endptr != '\0') {
        return 1;
    }
    unsigned int result = toggle_middle_bits(num);
    printf("%u\n", result);
    return 0;
}