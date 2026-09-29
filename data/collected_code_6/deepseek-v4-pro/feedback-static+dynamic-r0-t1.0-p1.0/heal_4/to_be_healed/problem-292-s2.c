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
     *  Condition 'divide(a,b,&quotient)==-1' is always false [knownConditionTrueFalse]
     *  Condition 'divide(a,b,&quotient)==-1' is always false
     *  Calling function 'divide' returns 0
     */
    if (divide(a, b, &quotient) == -1) {
        fprintf(stderr, "Error: Division by zero\n");
        return EXIT_FAILURE;
    }
    printf("Quotient: %d\n", quotient);

    int c = 7;
    int d = 0;
    int quotient2 = 0;
    /* Possible weaknesses found:
     *  Condition 'divide(c,d,&quotient2)==-1' is always true [knownConditionTrueFalse]
     *  Calling function 'divide' returns -1
     *  Condition 'divide(c,d,&quotient2)==-1' is always true
     */
    if (divide(c, d, &quotient2) == -1) {
        fprintf(stderr, "Error: Division by zero\n");
        return EXIT_FAILURE;
    }
    printf("Quotient: %d\n", quotient2);

    return EXIT_SUCCESS;
}