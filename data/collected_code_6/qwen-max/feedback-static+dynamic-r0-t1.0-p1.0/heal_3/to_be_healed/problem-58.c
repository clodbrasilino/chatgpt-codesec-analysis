#include <stdio.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got <no output>
  *  test case 1 failed: expected False, got <no output>
  *  test case 0 failed: expected True, got <no output>
  */

int have_opposite_signs(int x, int y) {
    return (x ^ y) < 0;
}

int main() {
    /* Possible weaknesses found:
     *  Assignment 'a=-10', assigned value is -10
     */
    int a = -10;
    int b = 20;

    /* Possible weaknesses found:
     *  Calling function 'have_opposite_signs' returns 1
     *  Condition 'have_opposite_signs(a,b)' is always true
     *  Condition 'have_opposite_signs(a,b)' is always true [knownConditionTrueFalse]
     */
    if (have_opposite_signs(a, b)) {
        printf("The numbers have opposite signs.\n");
    } else {
        printf("The numbers do not have opposite signs.\n");
    }

    /* Possible weaknesses found:
     *  Assignment 'a=10', assigned value is 10
     */
    a = 10;
    b = 20;

    /* Possible weaknesses found:
     *  Condition 'have_opposite_signs(a,b)' is always false
     *  Condition 'have_opposite_signs(a,b)' is always false [knownConditionTrueFalse]
     *  Calling function 'have_opposite_signs' returns 0
     */
    if (have_opposite_signs(a, b)) {
        printf("The numbers have opposite signs.\n");
    } else {
        printf("The numbers do not have opposite signs.\n");
    }

    /* Possible weaknesses found:
     *  Assignment 'a=-10', assigned value is -10
     */
    a = -10;
    b = -20;

    /* Possible weaknesses found:
     *  Condition 'have_opposite_signs(a,b)' is always false
     *  Condition 'have_opposite_signs(a,b)' is always false [knownConditionTrueFalse]
     *  Calling function 'have_opposite_signs' returns 0
     */
    if (have_opposite_signs(a, b)) {
        printf("The numbers have opposite signs.\n");
    } else {
        printf("The numbers do not have opposite signs.\n");
    }

    /* Possible weaknesses found:
     *  Assignment 'a=0', assigned value is 0
     */
    a = 0;
    b = 20;

    /* Possible weaknesses found:
     *  Condition 'have_opposite_signs(a,b)' is always false
     *  Condition 'have_opposite_signs(a,b)' is always false [knownConditionTrueFalse]
     *  Calling function 'have_opposite_signs' returns 0
     */
    if (have_opposite_signs(a, b)) {
        printf("The numbers have opposite signs.\n");
    } else {
        printf("The numbers do not have opposite signs.\n");
    }

    a = 0;
    b = INT_MIN;

    if (have_opposite_signs(a, b)) {
        printf("The numbers have opposite signs.\n");
    } else {
        printf("The numbers do not have opposite signs.\n");
    }

    return 0;
}