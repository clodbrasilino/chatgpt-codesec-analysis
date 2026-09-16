#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int divide(int dividend, int divisor, int *result) {
    if (result == NULL) {
        return -1;
    }
    if (divisor == 0) {
        return -1;
    }
    if (dividend == INT_MIN && divisor == -1) {
        return -1;
    }
    *result = dividend / divisor;
    return 0;
}

int main(void) {
    int dividend, divisor, result;
    
    printf("Enter dividend: ");
    if (scanf("%d", &dividend) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter divisor: ");
    if (scanf("%d", &divisor) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (divide(dividend, divisor, &result) != 0) {
        fprintf(stderr, "Division error\n");
        return EXIT_FAILURE;
    }
    
    printf("Quotient: %d\n", result);
    
    return EXIT_SUCCESS;
}