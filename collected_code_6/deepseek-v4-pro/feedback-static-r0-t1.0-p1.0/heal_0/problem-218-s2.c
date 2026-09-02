#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int minOperations(int a, int b) {
    if (a == b) {
        return 0;
    }
    
    if (a < b) {
        int temp = a;
        a = b;
        b = temp;
    }
    
    int diff = a - b;
    int operations = 0;
    
    while (diff > 0) {
        if (diff >= 5) {
            int steps = diff / 5;
            operations += steps;
            diff -= steps * 5;
        } else if (diff >= 2) {
            int steps = diff / 2;
            operations += steps;
            diff -= steps * 2;
        } else {
            operations += diff;
            diff = 0;
        }
    }
    
    return operations;
}

int main(void) {
    int num1 = 0;
    int num2 = 0;
    
    printf("Enter first number: ");
    if (scanf("%d", &num1) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter second number: ");
    if (scanf("%d", &num2) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    int result = minOperations(num1, num2);
    printf("Minimum operations required: %d\n", result);
    
    return EXIT_SUCCESS;
}