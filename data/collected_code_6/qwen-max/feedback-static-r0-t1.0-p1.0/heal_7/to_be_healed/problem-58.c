#include <stdio.h>

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

    return 0;
}