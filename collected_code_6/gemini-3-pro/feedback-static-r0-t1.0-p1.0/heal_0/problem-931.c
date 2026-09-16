#include <stdio.h>
#include <stdlib.h>

unsigned long long calculate_sum_of_cubes(int n) {
    if (n < 1) {
        return 0;
    }
    
    unsigned long long sum = 0;
    for (int i = 1; i <= n; i++) {
        unsigned long long term = (unsigned long long)i * i * i;
        if (sum > __LONG_LONG_MAX__ - term) {
            fprintf(stderr, "Integer overflow detected.\n");
            exit(EXIT_FAILURE);
        }
        sum += term;
    }
    return sum;
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }
    
    if (n < 1) {
        fprintf(stderr, "Input must be a positive integer.\n");
        return EXIT_FAILURE;
    }
    
    unsigned long long result = calculate_sum_of_cubes(n);
    printf("%llu\n", result);
    
    return EXIT_SUCCESS;
}