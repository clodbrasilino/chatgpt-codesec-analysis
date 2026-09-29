#include <stdio.h>
#include <stdlib.h>

unsigned long long cube_sum_even_natural(int n) {
    if (n < 0) {
        fprintf(stderr, "Error: Input must be non-negative.\n");
        exit(EXIT_FAILURE);
    }
    
    unsigned long long sum = 0;
    for (int i = 1; i <= n; i++) {
        unsigned long long even_num = 2ULL * i;
        sum += even_num * even_num * even_num;
    }
    return sum;
}

int main(void) {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: Invalid input.\n");
        return EXIT_FAILURE;
    }
    
    unsigned long long result = cube_sum_even_natural(n);
    printf("Cube sum of first %d even natural numbers: %llu\n", n, result);
    
    return EXIT_SUCCESS;
}