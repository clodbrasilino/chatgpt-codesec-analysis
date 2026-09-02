#include <stdio.h>
#include <stdlib.h>

long long sum_of_squares_of_odd_numbers(int n) {
    if (n <= 0) {
        return 0;
    }
    return (long long)n * (2 * n - 1) * (2 * n + 1) / 3;
}

int main(void) {
    int n;
    char input[32];
    char *endptr;
    
    printf("Enter a positive integer n: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    n = (int)strtol(input, &endptr, 10);
    
    if (endptr == input || *endptr != '\n') {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }
    
    if (n <= 0) {
        fprintf(stderr, "n must be a positive integer.\n");
        return EXIT_FAILURE;
    }
    
    printf("Sum of squares of first %d odd natural numbers: %lld\n", 
           n, sum_of_squares_of_odd_numbers(n));
    
    return EXIT_SUCCESS;
}