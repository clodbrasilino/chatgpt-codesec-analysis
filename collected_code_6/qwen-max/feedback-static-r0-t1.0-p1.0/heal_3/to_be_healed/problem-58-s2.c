#include <stdio.h>

int have_opposite_signs(int x, int y) {
    return (x ^ y) < 0;
}

int main() {
    /* Possible weaknesses found:
     *  Assignment 'a=-5', assigned value is -5
     */
    int a = -5;
    int b = 10;

    /* Possible weaknesses found:
     *  Calling function 'have_opposite_signs' returns 1
     *  Condition 'have_opposite_signs(a,b)' is always true
     *  Condition 'have_opposite_signs(a,b)' is always true [knownConditionTrueFalse]
     */
    if (have_opposite_signs(a, b)) {
        printf("The integers have opposite signs.\n");
    } else {
        printf("The integers do not have opposite signs.\n");
    }

    /* Possible weaknesses found:
     *  Assignment 'a=5', assigned value is 5
     */
    a = 5;
    b = 10;

    /* Possible weaknesses found:
     *  Calling function 'have_opposite_signs' returns 0
     *  Condition 'have_opposite_signs(a,b)' is always false
     *  Condition 'have_opposite_signs(a,b)' is always false [knownConditionTrueFalse]
     */
    if (have_opposite_signs(a, b)) {
        printf("The integers have opposite signs.\n");
    } else {
        printf("The integers do not have opposite signs.\n");
    }

    return 0;
}