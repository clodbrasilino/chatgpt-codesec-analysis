#include <stdio.h>
#include <stdlib.h>

long long sum_of_squares(int n) {
    if (n < 1) {
        return 0;
    }
    return (long long)n * (n + 1) * (2 * n + 1) / 6;
}

int main(void) {
    int n;
    long long result;
    
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 1) {
        printf("Please enter a positive integer\n");
        return EXIT_FAILURE;
    }
    
    result = sum_of_squares(n);
    printf("Sum of squares from 1 to %d is %lld\n", n, result);
    
    return EXIT_SUCCESS;
}