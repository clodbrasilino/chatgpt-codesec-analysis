#include <stdio.h>
#include <stdlib.h>

int find_remainder(int dividend, int divisor) {
    if (divisor == 0) {
        fprintf(stderr, "Error: Division by zero\n");
        exit(EXIT_FAILURE);
    }
    
    int quotient = dividend / divisor;
    int remainder = dividend - (quotient * divisor);
    return remainder;
}

int main(void) {
    int a = 17;
    int b = 5;
    int result = find_remainder(a, b);
    printf("Remainder of %d / %d is %d\n", a, b, result);
    
    return 0;
}