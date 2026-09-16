#include <stdio.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 1, got 30
  *  test case 0 failed: expected 1, got 31
  *  test case 1 failed: expected 2, got 31
  */

int count_unset_bits(unsigned int num) {
    int unset_bits = 0;
    for (int i = 0; i < sizeof(num) * CHAR_BIT; ++i) {
        if (!(num & (1U << i))) {
            ++unset_bits;
        }
    }
    return unset_bits;
}

int main() {
    unsigned int number = 0xAAAAAAAA;
    int result = count_unset_bits(number);
    printf("Number of unset bits: %d\n", result);
    return 0;
}