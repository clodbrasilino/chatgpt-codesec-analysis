#include <stdio.h>
#include <stdlib.h>

unsigned long long count_max_equilateral_triangles(unsigned long long n) {
    if (n % 2 == 0) {
        return (n * (n + 2) * (2 * n + 1)) / 8;
    } else {
        return ((n * (n + 2) * (2 * n + 1)) - 1) / 8;
    }
}

int main(void) {
    long long input = 0;
    
    if (scanf("%lld", &input) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (input < 0) {
        fprintf(stderr, "Input cannot be negative\n");
        return 1;
    }
    
    unsigned long long n = (unsigned long long)input;
    unsigned long long result = count_max_equilateral_triangles(n);
    
    printf("%llu\n", result);
    
    return 0;
}