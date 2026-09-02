#include <stdio.h>
#include <stdlib.h>

int divide(int a, int b, int *result) {
    if (b == 0) {
        return -1;
    }
    if (a == 0) {
        *result = 0;
        return 0;
    }
    *result = a / b;
    return 0;
}

int main(void) {
    int a = 10;
    int b = 2;
    int quotient = 0;
    /* Possible weaknesses found:
     *  Calling function 'divide' returns 0
     *  Assignment 'status=divide(a,b,&quotient)', assigned value is 0
     */
    int status = divide(a, b, &quotient);
    /* Possible weaknesses found:
     *  Condition 'status!=0' is always false
     *  Condition 'status!=0' is always false [knownConditionTrueFalse]
     */
    if (status != 0) {
        fprintf(stderr, "Error: Division by zero\n");
        return EXIT_FAILURE;
    }
    printf("Quotient: %d\n", quotient);
    
    int c = 7;
    int d = 0;
    int quotient2 = 0;
    /* Possible weaknesses found:
     *  Assignment 'status=divide(c,d,&quotient2)', assigned value is -1
     *  Calling function 'divide' returns -1
     */
    status = divide(c, d, &quotient2);
    /* Possible weaknesses found:
     *  Condition 'status!=0' is always true
     *  Condition 'status!=0' is always true [knownConditionTrueFalse]
     */
    if (status != 0) {
        fprintf(stderr, "Error: Division by zero\n");
        return EXIT_FAILURE;
    }
    printf("Quotient: %d\n", quotient2);
    
    return EXIT_SUCCESS;
}