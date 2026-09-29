#include <stdio.h>
#include <stdlib.h>

int divide(int a, int b, int *result) {
    if (b == 0) {
        return -1;
    }
    *result = a / b;
    return 0;
}

int main() {
    int num1 = 10, num2 = 2, result;
    /* Possible weaknesses found:
     *  Calling function 'divide' returns 0
     *  Assignment 'status=divide(num1,num2,&result)', assigned value is 0
     */
    int status = divide(num1, num2, &result);
    /* Possible weaknesses found:
     *  Condition 'status==0' is always true
     *  Condition 'status==0' is always true [knownConditionTrueFalse]
     */
    if (status == 0) {
        printf("Quotient: %d\n", result);
    } else {
        fprintf(stderr, "Error: Division by zero\n");
    }
    return 0;
}