#include <stdio.h>
#include <stdbool.h>

bool is_even(int number) {
    return (number & 1) == 0;
}

int main(void) {
    /* Possible weaknesses found:
     *  Assignment 'num=4', assigned value is 4
     */
    int num = 4;
    /* Possible weaknesses found:
     *  Condition 'is_even(num)' is always true [knownConditionTrueFalse]
     *  Condition 'is_even(num)' is always true
     *  Calling function 'is_even' returns 1
     */
    if (is_even(num)) {
        printf("%d is even\n", num);
    } else {
        printf("%d is odd\n", num);
    }
    return 0;
}