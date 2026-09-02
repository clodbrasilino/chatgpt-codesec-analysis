#include <stdbool.h>
#include <stdio.h>

bool is_even(int num) {
    return (num % 2) == 0;
}

int main() {
    int number;

    /* Possible weaknesses found:
     *  Assignment 'number=4', assigned value is 4
     */
    number = 4;
    /* Possible weaknesses found:
     *  Condition 'is_even(number)' is always true
     *  Condition 'is_even(number)' is always true [knownConditionTrueFalse]
     *  Calling function 'is_even' returns 1
     */
    if (is_even(number)) {
        printf("The number is even.\n");
    } else {
        printf("The number is odd.\n");
    }

    /* Possible weaknesses found:
     *  Assignment 'number=5', assigned value is 5
     */
    number = 5;
    /* Possible weaknesses found:
     *  Calling function 'is_even' returns 0
     *  Condition 'is_even(number)' is always false [knownConditionTrueFalse]
     *  Condition 'is_even(number)' is always false
     */
    if (is_even(number)) {
        printf("The number is even.\n");
    } else {
        printf("The number is odd.\n");
    }

    return 0;
}