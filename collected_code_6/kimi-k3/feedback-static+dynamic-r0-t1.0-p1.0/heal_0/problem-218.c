#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int min_operations_to_equal(long long a, long long b, long long *result) {
    long long diff;
    long long abs_diff;
    
    if (result == NULL) {
        return -1;
    }
    
    if (a == b) {
        *result = 0;
        return 0;
    }
    
    if (a > b) {
        if (a > 0 && b < 0 && a > LLONG_MAX + b) {
            return -1;
        }
        diff = a - b;
    } else {
        if (b > 0 && a < 0 && b > LLONG_MAX + a) {
            return -1;
        }
        diff = b - a;
    }
    
    abs_diff = diff;
    
    *result = abs_diff;
    return 0;
}

int main(void) {
    long long num1;
    long long num2;
    long long operations;
    int status;
    
    printf("Enter first number: ");
    if (scanf("%lld", &num1) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter second number: ");
    if (scanf("%lld", &num2) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    status = min_operations_to_equal(num1, num2, &operations);
    
    if (status != 0) {
        fprintf(stderr, "Error calculating operations\n");
        return EXIT_FAILURE;
    }
    
    printf("Minimum operations required: %lld\n", operations);
    
    return EXIT_SUCCESS;
}