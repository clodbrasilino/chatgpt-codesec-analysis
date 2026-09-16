#include <stdio.h>
#include <stdlib.h>

int find_quotient(int dividend, int divisor, int *result) {
    if (divisor == 0 || result == NULL) {
        return -1;
    }
    
    *result = dividend / divisor;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int dividend;
    int divisor;
    int quotient = 0;
    int status;
    
    if (argc == 3) {
        dividend = atoi(argv[1]);
        divisor = atoi(argv[2]);
    } else {
        dividend = 20;
        divisor = 4;
    }
    
    status = find_quotient(dividend, divisor, &quotient);
    if (status == 0) {
        printf("Quotient: %d\n", quotient);
    } else {
        printf("Error: Division by zero or invalid pointer.\n");
    }
    
    return EXIT_SUCCESS;
}