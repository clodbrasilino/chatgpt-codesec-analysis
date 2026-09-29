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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int dividend = 20;
    int divisor = 4;
    int quotient = 0;
    
    if (find_quotient(dividend, divisor, &quotient) == 0) {
        printf("Quotient: %d\n", quotient);
    } else {
        printf("Error: Division by zero or invalid pointer.\n");
    }
    
    dividend = 15;
    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    divisor = argc > 1 ? atoi(argv[1]) : 0;
    
    if (find_quotient(dividend, divisor, &quotient) == 0) {
        printf("Quotient: %d\n", quotient);
    } else {
        printf("Error: Division by zero or invalid pointer.\n");
    }
    
    return EXIT_SUCCESS;
}