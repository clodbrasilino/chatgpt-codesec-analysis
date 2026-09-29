#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got <no output>
  *  test case 1 failed: expected True, got <no output>
  *  test case 0 failed: expected False, got <no output>
  */

bool is_even(int num) {
    return (num & 1) == 0;
}

int main() {
    /* Possible weaknesses found:
     *  Assignment 'number=4', assigned value is 4
     */
    int number = 4;
    /* Possible weaknesses found:
     *  Condition 'is_even(number)' is always true
     *  Condition 'is_even(number)' is always true [knownConditionTrueFalse]
     *  Calling function 'is_even' returns 1
     */
    if (is_even(number)) {
        printf("%d is even\n", number);
    } else {
        printf("%d is odd\n", number);
    }
    return 0;
}