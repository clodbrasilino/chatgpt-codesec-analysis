#include <stdio.h>
#include <math.h>
#include <limits.h>

long next_perfect_square(long n) {
    if (n < 0) {
        return 0;
    }
    
    if (n >= LONG_MAX - 1) {
        return -1;
    }
    
    double sqrt_val = sqrt((double)n);
    if (sqrt_val >= (double)LONG_MAX || sqrt_val != sqrt_val) {
        return -1;
    }
    
    long root = (long)sqrt_val;
    
    if (root > 0 && root > LONG_MAX / root) {
        return -1;
    }
    
    long square = root * root;
    
    if (square <= n) {
        if (root >= LONG_MAX - 1) {
            return -1;
        }
        root++;
        if (root > 0 && root > LONG_MAX / root) {
            return -1;
        }
        square = root * root;
    }
    
    return square;
}

int main(void) {
    long test_values[] = {0, 1, 15, 16, 17, 25, 100, -5};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        long result = next_perfect_square(test_values[i]);
        if (result == -1) {
            printf("Input: %ld, Result: Overflow occurred\n", test_values[i]);
        } else {
            printf("Input: %ld, Result: %ld\n", test_values[i], result);
        }
    }
    
    return 0;
}