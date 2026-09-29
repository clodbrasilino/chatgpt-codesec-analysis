#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int find_quotient(int dividend, int divisor, int *result) {
    if (divisor == 0 || (dividend == INT_MIN && divisor == -1)) {
        return -1;
    }
    
    if (result != NULL) {
        *result = dividend / divisor;
        return 0;
    }
    
    return -1;
}

int main(int argc, const char *argv[]) {
    int dividend = 20;
    int divisor = 4;
    int quotient = 0;
    
    if (find_quotient(dividend, divisor, &quotient) == 0) {
        printf("Quotient: %d\n", quotient);
    } else {
        printf("Error: Division by zero or invalid pointer.\n");
    }
    
    dividend = 15;
    divisor = 0;
    
    if (argc > 1) {
        char *endptr;
        errno = 0;
        long parsed_val = strtol(argv[1], &endptr, 10);
        
        if (errno == 0 && *endptr == '\0' && endptr != argv[1] && parsed_val >= INT_MIN && parsed_val <= INT_MAX) {
            divisor = (int)parsed_val;
        } else {
            divisor = 0;
        }
    }
    
    if (find_quotient(dividend, divisor, &quotient) == 0) {
        printf("Quotient: %d\n", quotient);
    } else {
        printf("Error: Division by zero or invalid pointer.\n");
    }
    
    return EXIT_SUCCESS;
}