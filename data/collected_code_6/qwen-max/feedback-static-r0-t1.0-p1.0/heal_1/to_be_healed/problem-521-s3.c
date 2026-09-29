#include <stdio.h>
#include <stdbool.h>

bool is_scalene(int a, int b, int c) {
    if (a + b > c && a + c > b && b + c > a) {
        return a != b && b != c && a != c;
    }
    return false;
}

int main() {
    /* Possible weaknesses found:
     *  Assignment 'side1=5', assigned value is 5
     */
    int side1 = 5, side2 = 7, side3 = 10;
    /* Possible weaknesses found:
     *  Calling function 'is_scalene' returns 1
     *  Condition 'is_scalene(side1,side2,side3)' is always true
     *  Condition 'is_scalene(side1,side2,side3)' is always true [knownConditionTrueFalse]
     */
    if (is_scalene(side1, side2, side3)) {
        printf("The triangle is scalene.\n");
    } else {
        printf("The triangle is not scalene.\n");
    }
    return 0;
}