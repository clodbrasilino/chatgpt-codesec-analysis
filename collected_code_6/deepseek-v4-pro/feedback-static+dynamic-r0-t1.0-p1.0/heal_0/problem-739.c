#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <errno.h>

unsigned long long find_smallest_triangular_index(int n) {
    if (n <= 0) {
        return 0;
    }
    
    if (n == 1) {
        return 1;
    }
    
    long double lower_bound = powl(10.0L, (long double)(n - 1));
    long double upper_bound = powl(10.0L, (long double)n) - 1.0L;
    
    long double sqrt_val = sqrtl(1.0L + 8.0L * lower_bound);
    long double index_estimate = (-1.0L + sqrt_val) / 2.0L;
    
    unsigned long long idx = (unsigned long long)ceill(index_estimate);
    
    if (idx < 1) {
        idx = 1;
    }
    
    while (1) {
        if (idx > (unsigned long long)(-1) / (idx + 1) / 2) {
            return 0;
        }
        
        unsigned long long triangular = idx * (idx + 1) / 2;
        
        if (triangular >= (unsigned long long)lower_bound && triangular <= (unsigned long long)upper_bound) {
            return idx;
        }
        
        if (triangular > (unsigned long long)upper_bound) {
            break;
        }
        
        idx++;
        
        if (idx > 1000000000ULL) {
            return 0;
        }
    }
    
    return 0;
}

int main(void) {
    int test_cases[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 18, 0, -5};
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int i = 0; i < num_tests; i++) {
        int n = test_cases[i];
        unsigned long long result = find_smallest_triangular_index(n);
        
        if (n <= 0) {
            printf("n = %d: Invalid input\n", n);
            continue;
        }
        
        if (result == 0) {
            printf("n = %d: Result exceeds limits or no valid index\n", n);
        } else {
            printf("n = %d: index = %llu\n", n, result);
        }
    }
    
    return 0;
}