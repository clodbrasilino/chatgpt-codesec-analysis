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
    int num1 = 10, num2 = 0, result;
    /* Possible weaknesses found:
     *  Assignment 'status=divide(num1,num2,&result)', assigned value is -1
     *  Calling function 'divide' returns -1
     */
    int status = divide(num1, num2, &result);
    /* Possible weaknesses found:
     *  Condition 'status==0' is always false
     *  Condition 'status==0' is always false [knownConditionTrueFalse]
     */
    if (status == 0) {
        printf("Quotient: %d\n", result);
    } else {
        fprintf(stderr, "Error: Division by zero\n");
    }
    return 0;
}