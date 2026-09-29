#include <stdio.h>
#include <stdbool.h>

bool is_even(int number) {
    return (number % 2) == 0;
}

int main(void) {
    /* Possible weaknesses found:
     *  Assignment 'test_number=42', assigned value is 42
     */
    int test_number = 42;
    
    /* Possible weaknesses found:
     *  Calling function 'is_even' returns 1
     *  Condition 'is_even(test_number)' is always true
     *  Condition 'is_even(test_number)' is always true [knownConditionTrueFalse]
     */
    if (is_even(test_number)) {
        printf("%d is even.\n", test_number);
    } else {
        printf("%d is odd.\n", test_number);
    }
    
    /* Possible weaknesses found:
     *  Assignment 'test_number=43', assigned value is 43
     */
    test_number = 43;
    
    /* Possible weaknesses found:
     *  Condition 'is_even(test_number)' is always false
     *  Condition 'is_even(test_number)' is always false [knownConditionTrueFalse]
     *  Calling function 'is_even' returns 0
     */
    if (is_even(test_number)) {
        printf("%d is even.\n", test_number);
    } else {
        printf("%d is odd.\n", test_number);
    }
    
    return 0;
}