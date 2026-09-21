#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int find_quotient(int dividend, int divisor, int *result) {
    if (divisor == 0 || result == NULL) {
        return -1;
    }
    
    if (dividend == INT_MIN && divisor == -1) {
        return -1;
    }
    
    *result = dividend / divisor;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[]) {
    int dividend;
    int divisor;
    int quotient = 0;
    int status;
    
    if (argc == 3) {
        char *endptr;
        long temp_val;
        
        errno = 0;
        temp_val = strtol(argv[1], &endptr, 10);
        if (errno != 0 || *endptr != '\0' || temp_val < INT_MIN || temp_val > INT_MAX) {
            printf("Error: Invalid dividend input.\n");
            return EXIT_FAILURE;
        }
        dividend = (int)temp_val;
        
        errno = 0;
        temp_val = strtol(argv[2], &endptr, 10);
        if (errno != 0 || *endptr != '\0' || temp_val < INT_MIN || temp_val > INT_MAX) {
            printf("Error: Invalid divisor input.\n");
            return EXIT_FAILURE;
        }
        divisor = (int)temp_val;
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