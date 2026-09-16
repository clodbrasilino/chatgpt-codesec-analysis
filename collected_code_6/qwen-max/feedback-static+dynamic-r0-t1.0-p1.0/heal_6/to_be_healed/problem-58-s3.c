#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got <no output>
  *  test case 1 failed: expected False, got <no output>
  *  test case 0 failed: expected True, got <no output>
  */

int have_opposite_signs(int a, int b) {
    return (a ^ b) < 0;
}

int main() {
    /* Possible weaknesses found:
     *  Assignment 'x=-10', assigned value is -10
     */
    int x = -10;
    int y = 20;

    /* Possible weaknesses found:
     *  Calling function 'have_opposite_signs' returns 1
     *  Condition 'have_opposite_signs(x,y)' is always true [knownConditionTrueFalse]
     *  Condition 'have_opposite_signs(x,y)' is always true
     */
    if (have_opposite_signs(x, y)) {
        printf("The numbers have opposite signs.\n");
    } else {
        printf("The numbers do not have opposite signs.\n");
    }

    /* Possible weaknesses found:
     *  Assignment 'x=10', assigned value is 10
     */
    x = 10;

    /* Possible weaknesses found:
     *  Condition 'have_opposite_signs(x,y)' is always false
     *  Condition 'have_opposite_signs(x,y)' is always false [knownConditionTrueFalse]
     *  Calling function 'have_opposite_signs' returns 0
     */
    if (have_opposite_signs(x, y)) {
        printf("The numbers have opposite signs.\n");
    } else {
        printf("The numbers do not have opposite signs.\n");
    }

    return 0;
}