#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int minOperations(int a, int b) {
    if (a == b) {
        return 0;
    }
    
    long long diff = llabs((long long)a - (long long)b);
    int operations = 0;
    
    operations += diff / 5;
    diff %= 5;
    
    operations += diff / 2;
    diff %= 2;
    
    if (diff == 1) {
        operations += 1;
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