#include <stdio.h>
#include <stdbool.h>

bool is_odd(int num) {
    return (num & 1) != 0;
}

int main() {
    /* Possible weaknesses found:
     *  Assignment 'number=7', assigned value is 7
     */
    int number = 7;
    /* Possible weaknesses found:
     *  Condition 'is_odd(number)' is always true
     *  Condition 'is_odd(number)' is always true [knownConditionTrueFalse]
     *  Calling function 'is_odd' returns 1
     */
    if (is_odd(number)) {
        printf("The number is odd.\n");
    } else {
        printf("The number is not odd.\n");
    }
    return 0;
}