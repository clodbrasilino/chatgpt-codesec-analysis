#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

long long sum_of_cubes(int n) {
    if (n < 0) {
        return 0;
    }
    
    if (n > 2097151) {
        fprintf(stderr, "Error: n=%d is too large, overflow would occur\n", n);
        return -1;
    }
    
    long long sum = (long long)n * (n + 1);
    if (sum % 2 != 0) {
        fprintf(stderr, "Error: unexpected odd sum for n=%d\n", n);
        return -1;
    }
    sum /= 2;
    
    if (sum > 0 && sum > LLONG_MAX / sum) {
        fprintf(stderr, "Error: multiplication overflow for n=%d\n", n);
        return -1;
    }
    
    return sum * sum;
}

int main(void) {
    int n;
    
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        fprintf(stderr, "Input must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    if (n > 2097151) {
        fprintf(stderr, "Input too large, would cause overflow\n");
        return EXIT_FAILURE;
    }
    
    long long result = sum_of_cubes(n);
    if (result == -1) {
        fprintf(stderr, "Computation failed\n");
        return EXIT_FAILURE;
    }
    
    printf("Sum of cubes from 1 to %d is %lld\n", n, result);
    
    return EXIT_SUCCESS;
}