#include <stdbool.h>
#include <stdio.h>

bool is_even(int num) {
    return (num % 2) == 0;
}

int main() {
    /* Possible weaknesses found:
     *  Assignment 'number=4', assigned value is 4
     */
    int number = 4;

    /* Possible weaknesses found:
     *  Condition 'is_even(number)' is always true [knownConditionTrueFalse]
     *  Calling function 'is_even' returns 1
     *  Condition 'is_even(number)' is always true
     */
    if (is_even(number)) {
        printf("The number is even.\n");
    } else {
        printf("The number is odd.\n");
    }

    return 0;
}