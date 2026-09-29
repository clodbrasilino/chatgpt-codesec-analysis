#include <stdbool.h>
#include <stdio.h>

bool is_even(int num) {
    return (num % 2) == 0;
}

int main() {
    /* Possible weaknesses found:
     *  Assignment 'number=4', assigned value is 4
     */
    int number = 4; // Example number
    /* Possible weaknesses found:
     *  Condition 'is_even(number)' is always true
     *  Condition 'is_even(number)' is always true [knownConditionTrueFalse]
     *  Calling function 'is_even' returns 1
     */
    if (is_even(number)) {
        printf("%d is even.\n", number);
    } else {
        printf("%d is not even.\n", number);
    }
    return 0;
}