#include <stdio.h>
#include <stdint.h>

uint32_t set_leftmost_unset_bit(uint32_t n);
 /* Possible weaknesses found:
  *  test case 1 failed: expected 14, got 2147483660
  *  test case 0 failed: expected 14, got 2147483658
  *  test case 2 failed: expected 15, got 2147483663
  */

uint32_t set_leftmost_unset_bit(uint32_t n) {
    /* Possible weaknesses found:
     *  Assignment 'inverted=~n', assigned value is greater than 0
     */
    uint32_t inverted = ~n;
    uint32_t pos = 31;

    /* Possible weaknesses found:
     *  Condition 'inverted==0' is always false
     *  Condition 'inverted==0' is always false [knownConditionTrueFalse]
     */
    if (inverted == 0) {
        return n;
    }

    while ((inverted & (1U << pos)) == 0 && pos > 0) {
        pos--;
    }

    return n | (1U << pos);
}

int main(void) {
    uint32_t test_val1 = 0x7FFFFFFF;
    uint32_t test_val2 = 0x0FFFFFFF;
    uint32_t test_val3 = 0xFFFFFFFF;
    
    uint32_t res1 = set_leftmost_unset_bit(test_val1);
    uint32_t res2 = set_leftmost_unset_bit(test_val2);
    uint32_t res3 = set_leftmost_unset_bit(test_val3);

    printf("%u\n", res1);
    printf("%u\n", res2);
    printf("%u\n", res3);

    return 0;
}