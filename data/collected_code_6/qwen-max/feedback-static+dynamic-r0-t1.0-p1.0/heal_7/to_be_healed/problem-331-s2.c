#include <stdio.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 1, got 2
  *  test case 1 failed: expected 2, got 1
  */

int count_set_bits(unsigned int num) {
    int set_bits = 0;
    while (num) {
        set_bits += num & 1;
        num >>= 1;
    }
    return set_bits;
}

int main() {
    unsigned int number = 0xAAAAAAAA;
    int unset_bits = sizeof(number) * CHAR_BIT - count_set_bits(number);
    printf("Number of unset bits: %d\n", unset_bits);

    printf("%d\n", count_set_bits(1));
    printf("%d\n", count_set_bits(3));
    printf("%d\n", count_set_bits(UINT_MAX));

    return 0;
}