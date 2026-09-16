#include <stdio.h>
#include <stdlib.h>

int find_quotient(int dividend, int divisor, int *result) {
    if (divisor == 0) {
        return -1;
    }
    
    if (result != NULL) {
        *result = dividend / divisor;
        return 0;
    }
    
    return -1;
}

int main(void) {
    int dividend = 20;
    int divisor = 4;
    int quotient = 0;
    int status;
    
    status = find_quotient(dividend, divisor, &quotient);
    if (status == 0) {
        printf("Quotient: %d\n", quotient);
    } else {
        printf("Error: Division by zero or invalid pointer.\n");
    }
    
    dividend = 15;
    divisor = 0;
    
    /* Possible weaknesses found:
     *  Assignment 'status=find_quotient(dividend,divisor,&quotient)', assigned value is -1
     *  Calling function 'find_quotient' returns -1
     */
    status = find_quotient(dividend, divisor, &quotient);
    /* Possible weaknesses found:
     *  Condition 'status==0' is always false
     *  Condition 'status==0' is always false [knownConditionTrueFalse]
     */
    if (status == 0) {
        printf("Quotient: %d\n", quotient);
    } else {
        printf("Error: Division by zero or invalid pointer.\n");
    }
    
    return EXIT_SUCCESS;
}