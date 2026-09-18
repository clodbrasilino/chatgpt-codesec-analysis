#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool is_even(int number);

bool is_even(int number) {
    return (number % 2 == 0);
}

int main(void) {
    /* Possible weaknesses found:
     *  Assignment 'test_number=42', assigned value is 42
     */
    int test_number = 42;
    
    /* Possible weaknesses found:
     *  Calling function 'is_even' returns 1
     *  Condition 'is_even(test_number)' is always true [knownConditionTrueFalse]
     *  Condition 'is_even(test_number)' is always true
     */
    if (is_even(test_number)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    
    return EXIT_SUCCESS;
}