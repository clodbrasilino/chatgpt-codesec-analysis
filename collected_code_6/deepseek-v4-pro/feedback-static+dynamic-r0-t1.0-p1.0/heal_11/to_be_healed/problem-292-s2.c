#include <stdio.h>
#include <stdlib.h>

int divide(int a, int b, int *result) {
    if (b == 0) {
        return -1;
    }
    if (result == NULL) {
        return -2;
    }
    *result = a / b;
    return 0;
}

int main(void) {
    int a = 10;
    int b = 2;
    int quotient = 0;
    int ret;

    ret = divide(a, b, &quotient);
    if (ret != 0) {
        fprintf(stderr, "Error: Division failed\n");
        return EXIT_FAILURE;
    }
    printf("Quotient: %d\n", quotient);

    int c = 7;
    int d = 0;
    int quotient2 = 0;

    /* Possible weaknesses found:
     *  Assignment 'ret=divide(c,d,&quotient2)', assigned value is -1
     *  Calling function 'divide' returns -1
     */
    ret = divide(c, d, &quotient2);
    /* Possible weaknesses found:
     *  Condition 'ret!=0' is always true [knownConditionTrueFalse]
     *  Condition 'ret!=0' is always true
     */
    if (ret != 0) {
        /* Possible weaknesses found:
         *  Condition 'ret==-1' is always true
         *  Condition 'ret==-1' is always true [knownConditionTrueFalse]
         */
        if (ret == -1) {
            fprintf(stderr, "Error: Division by zero\n");
        } else if (ret == -2) {
            fprintf(stderr, "Error: Invalid result pointer\n");
        } else {
            fprintf(stderr, "Error: Division failed\n");
        }
        return EXIT_FAILURE;
    }

    printf("Quotient: %d\n", quotient2);
    return EXIT_SUCCESS;
}