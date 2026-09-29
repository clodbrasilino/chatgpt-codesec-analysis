#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long cube_sum_even(int n) {
    if (n <= 0) {
        return 0;
    }
    
    if (n > INT_MAX / 2) {
        return 0;
    }
    
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        int even_num = 2 * i;
        long long cube = (long long)even_num * even_num * even_num;
        
        if (sum > LLONG_MAX - cube) {
            return 0;
        }
        
        sum += cube;
    }
    
    return sum;
}

int main(void) {
    int n;
    
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (n < 0) {
        fprintf(stderr, "Input must be non-negative\n");
        return 1;
    }
    
    printf("Cube sum of first %d even natural numbers: %lld\n", 
           n, cube_sum_even(n));
    
    return 0;
}