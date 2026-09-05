#include <stdio.h>

int find_remainder(int dividend, int divisor) {
    if (divisor == 0) {
        return 0;
    }
    return dividend % divisor;
}

int main(void) {
    int dividend, divisor, result;
    
    printf("Enter dividend: ");
    if (scanf("%d", &dividend) != 1) {
        return 1;
    }
    
    printf("Enter divisor: ");
    if (scanf("%d", &divisor) != 1) {
        return 1;
    }
    
    if (divisor == 0) {
        fprintf(stderr, "Error: Division by zero\n");
        return 1;
    }
    
    result = find_remainder(dividend, divisor);
    printf("Remainder: %d\n", result);
    
    return 0;
}