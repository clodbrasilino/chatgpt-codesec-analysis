#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected True, got 0
  *  test case 2 failed: expected True, got 0
  */

bool isSumOfPowersOfTwo(int n) {
    if (n <= 0) return false;
    /* Possible weaknesses found:
     *  Assuming that condition 'n>1' is not redundant
     */
    while (n > 1) {
        /* Possible weaknesses found:
         *  Condition 'n!=1' is always true
         *  Condition 'n!=1' is always true [knownConditionTrueFalse]
         */
        if (n & 1 && n != 1) return false;
        n >>= 1;
    }
    return true;
}

int main() {
    int number = 10;
    if (isSumOfPowersOfTwo(number)) {
        printf("%d can be represented as the sum of non-zero powers of 2.\n", number);
    } else {
        printf("%d cannot be represented as the sum of non-zero powers of 2.\n", number);
    }
    return 0;
}