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
    int num1 = 10, num2 = 5, result;
    /* Possible weaknesses found:
     *  Calling function 'divide' returns 0
     *  Assignment 'status=divide(num1,num2,&result)', assigned value is 0
     */
    int status = divide(num1, num2, &result);
    /* Possible weaknesses found:
     *  Condition 'status!=0' is always false
     *  Condition 'status!=0' is always false [knownConditionTrueFalse]
     */
    if (status != 0) {
        fprintf(stderr, "Error: Division by zero\n");
    } else {
        printf("Quotient: %d\n", result);
    }
    return 0;
}