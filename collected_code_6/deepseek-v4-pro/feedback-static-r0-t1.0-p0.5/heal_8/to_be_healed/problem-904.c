#include <stdbool.h>

bool is_even(int number) {
    return number % 2 == 0;
}

int main(void) {
    /* Possible weaknesses found:
     *  Assignment 'test_number=11', assigned value is 11
     */
    int test_number = 11;
    /* Possible weaknesses found:
     *  Assignment 'result=is_even(test_number)', assigned value is 0
     *  Calling function 'is_even' returns 0
     */
    bool result = is_even(test_number);
    /* Possible weaknesses found:
     *  Condition 'result' is always false
     *  Condition 'result' is always false [knownConditionTrueFalse]
     */
    return result ? 0 : 1;
}