#include <stdio.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 15, got 31
  */

uint32_t set_rightmost_unset_bit(uint32_t n) {
    if (n == ~0U) {
        return n;
    }
    return n | (n + 1);
}

int main(void) {
    uint32_t test_value;
    /* Possible weaknesses found:
     *  The scope of the variable 'result' can be reduced. [variableScope]
     */
    uint32_t result;

    if (scanf("%u", &test_value) == 1) {
        result = set_rightmost_unset_bit(test_value);

        if (printf("%u\n", result) < 0) {
            return 1;
        }
    }

    return 0;
}