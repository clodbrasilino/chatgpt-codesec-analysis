#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 33, got <no output>
  *  test case 1 failed: expected 2, got <no output>
  *  test case 2 failed: expected 28, got <no output>
  */

unsigned int count_set_bits_up_to_n(unsigned int n) {
    if (n == 0) {
        return 0;
    }
    unsigned int msb_pos = 0;
    unsigned int temp = n;
    while (temp >>= 1) {
        msb_pos++;
    }
    unsigned int msb = 1U << msb_pos;
    unsigned int count = msb_pos * (msb >> 1);
    count += (n - msb + 1);
    count += count_set_bits_up_to_n(n - msb);
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);
    if (*endptr != '\0' || val > UINT32_MAX) {
        return EXIT_FAILURE;
    }
    unsigned int n = (unsigned int)val;
    unsigned int result = count_set_bits_up_to_n(n);
    printf("%u\n", result);
    return EXIT_SUCCESS;
}