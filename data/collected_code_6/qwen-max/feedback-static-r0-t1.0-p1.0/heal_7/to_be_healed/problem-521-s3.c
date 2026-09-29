#include <stdio.h>
#include <stdbool.h>

bool is_scalene(int a, int b, int c) {
    if (a + b > c && a + c > b && b + c > a && a != b && b != c && a != c) {
        return true;
    }
    return false;
}

int main() {
    int side1 = 5, side2 = 7, side3 = 10;
    /* Possible weaknesses found:
     *  Calling function 'is_scalene' returns 1
     *  Assignment 'result=is_scalene(side1,side2,side3)', assigned value is 1
     */
    bool result = is_scalene(side1, side2, side3);
    /* Possible weaknesses found:
     *  Condition 'result' is always true [knownConditionTrueFalse]
     *  Condition 'result' is always true
     */
    if (result) {
        printf("The triangle is scalene.\n");
    } else {
        printf("The triangle is not scalene.\n");
    }
    return 0;
}