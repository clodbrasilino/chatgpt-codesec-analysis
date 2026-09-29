#include <stdbool.h>

bool is_even(int number) {
    return number % 2 == 0;
}

int main(void) {
    /* Possible weaknesses found:
     *  Assignment 'test_number=10', assigned value is 10
     */
    int test_number = 10;
    /* Possible weaknesses found:
     *  Calling function 'is_even' returns 1
     *  Assignment 'result=is_even(test_number)', assigned value is 1
     */
    bool result = is_even(test_number);
    /* Possible weaknesses found:
     *  Condition 'result' is always true [knownConditionTrueFalse]
     *  Condition 'result' is always true
     */
    return result ? 0 : 1;
}