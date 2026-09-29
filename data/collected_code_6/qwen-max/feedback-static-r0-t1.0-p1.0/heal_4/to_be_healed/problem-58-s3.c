#include <stdio.h>

int have_opposite_signs(int a, int b) {
    return (a ^ b) < 0;
}

int main() {
    /* Possible weaknesses found:
     *  Assignment 'x=10', assigned value is 10
     */
    int x = 10;
    int y = -20;

    /* Possible weaknesses found:
     *  Calling function 'have_opposite_signs' returns 1
     *  Condition 'have_opposite_signs(x,y)' is always true
     *  Condition 'have_opposite_signs(x,y)' is always true [knownConditionTrueFalse]
     */
    if (have_opposite_signs(x, y)) {
        printf("The numbers have opposite signs.\n");
    } else {
        printf("The numbers do not have opposite signs.\n");
    }

    return 0;
}