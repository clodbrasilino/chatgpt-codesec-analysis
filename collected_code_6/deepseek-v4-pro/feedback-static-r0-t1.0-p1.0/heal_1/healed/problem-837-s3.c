#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long cube_sum_odd_natural(int n) {
    if (n <= 0) {
        return 0;
    }
    
    long long sum = 0;
    int count = 0;
    int num = 1;
    
    while (count < n) {
        long long cube = (long long)num * num * num;
        if (cube < 0 || sum > (long long)LLONG_MAX - cube) {
            fprintf(stderr, "Overflow detected\n");
            exit(EXIT_FAILURE);
        }
        sum += cube;
        num += 2;
        count++;
    }
    
    return sum;
}

int main(void) {
    int n;
    long long result;
    
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        fprintf(stderr, "n must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    result = cube_sum_odd_natural(n);
    printf("Cube sum of first %d odd natural numbers: %lld\n", n, result);
    
    return EXIT_SUCCESS;
}