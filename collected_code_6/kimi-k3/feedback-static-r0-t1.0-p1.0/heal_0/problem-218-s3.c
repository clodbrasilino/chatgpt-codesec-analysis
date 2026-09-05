#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int min_operations_to_equal(long a, long b) {
    if (a == b) {
        return 0;
    }
    
    long diff = labs(a - b);
    int operations = 0;
    
    while (diff > 0) {
        if (diff >= 5) {
            diff -= 5;
        } else if (diff >= 2) {
            diff -= 2;
        } else {
            diff -= 1;
        }
        operations++;
    }
    
    return operations;
}

int main(void) {
    long num1, num2;
    
    printf("Enter two numbers: ");
    
    if (scanf("%ld %ld", &num1, &num2) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    int result = min_operations_to_equal(num1, num2);
    printf("Minimum operations required: %d\n", result);
    
    return EXIT_SUCCESS;
}