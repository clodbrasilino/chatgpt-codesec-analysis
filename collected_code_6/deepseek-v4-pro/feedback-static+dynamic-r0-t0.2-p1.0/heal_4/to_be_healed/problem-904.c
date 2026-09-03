#include <stdbool.h>
#include <stdlib.h>

bool is_even(int number) {
    return number % 2 == 0;
}

int main(void) {
    /* Possible weaknesses found:
     *  Assignment 'test_number=42', assigned value is 42
     */
    int test_number = 42;
    /* Possible weaknesses found:
     *  Assignment 'result=is_even(test_number)', assigned value is 1
     *  Calling function 'is_even' returns 1
     */
    bool result = is_even(test_number);
    
    /* Possible weaknesses found:
     *  Condition 'result' is always true
     *  Condition 'result' is always true [knownConditionTrueFalse]
     */
    if (result) {
        return EXIT_SUCCESS;
    }
    
    return EXIT_FAILURE;
}