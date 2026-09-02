#include <stdio.h>
#include <stdlib.h>

long long sum_of_cubes(int n) {
    long long sum = (long long)n * (n + 1) / 2;
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
    
    printf("Sum of cubes from 1 to %d is %lld\n", n, sum_of_cubes(n));
    
    return EXIT_SUCCESS;
}