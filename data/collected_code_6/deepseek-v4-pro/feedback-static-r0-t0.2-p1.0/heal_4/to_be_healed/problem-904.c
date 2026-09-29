#include <stdbool.h>
#include <stdlib.h>

bool is_even(int number) {
    return number % 2 == 0;
}

int main(void) {
    int test_number;
    bool result;
    
    /* Possible weaknesses found:
     *  Assignment 'test_number=42', assigned value is 42
     */
    test_number = 42;
    /* Possible weaknesses found:
     *  Calling function 'is_even' returns 1
     *  Assignment 'result=is_even(test_number)', assigned value is 1
     */
    result = is_even(test_number);
    
    /* Possible weaknesses found:
     *  Condition 'result' is always true [knownConditionTrueFalse]
     *  Condition 'result' is always true
     */
    if (result) {
        return 0;
    }
    
    return 1;
}