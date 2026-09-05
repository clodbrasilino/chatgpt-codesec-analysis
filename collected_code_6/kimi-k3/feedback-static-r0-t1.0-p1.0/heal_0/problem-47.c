#include <stdio.h>
#include <stdlib.h>

int last_digit_factorial_quotient(int a, int b) {
    if (a < 0 || b < 0) {
        return -1;
    }
    
    if (a > b) {
        return -1;
    }
    
    if (a == b) {
        return 1;
    }
    
    int result = 1;
    int i;
    
    for (i = a + 1; i <= b; i++) {
        result = (result * (i % 10)) % 10;
        if (result == 0) {
            break;
        }
    }
    
    return result;
}

int main(void) {
    int a, b;
    int result;
    
    if (scanf("%d %d", &a, &b) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    result = last_digit_factorial_quotient(a, b);
    
    if (result == -1) {
        fprintf(stderr, "Invalid input values\n");
        return EXIT_FAILURE;
    }
    
    printf("%d\n", result);
    
    return EXIT_SUCCESS;
}