#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 2, got 31
  *  test case 2 failed: expected 1, got 30
  *  test case 0 failed: expected 1, got 31
  */

int count_unset_bits(unsigned int n) {
    int count = 0;
    int bits = sizeof(n) * CHAR_BIT;
    for (int i = 0; i < bits; i++) {
        count += !(n & 1);
        n >>= 1;
    }
    return count;
}

int main(int argc, char * const * argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);
    if (*endptr != '\0' || val > UINT32_MAX) {
        fprintf(stderr, "Invalid input or out of range\n");
        return EXIT_FAILURE;
    }
    unsigned int num = (unsigned int)val;
    int unset_bits = count_unset_bits(num);
    printf("%d\n", unset_bits);
    return EXIT_SUCCESS;
}