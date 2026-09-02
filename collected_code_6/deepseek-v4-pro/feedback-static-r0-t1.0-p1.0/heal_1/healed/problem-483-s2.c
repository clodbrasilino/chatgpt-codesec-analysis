#include <stdio.h>
#include <stdlib.h>

unsigned long long factorial_mod(unsigned long long n, unsigned long long mod) {
    unsigned long long result = 1;
    for (unsigned long long i = 2; i <= n && result != 0; i++) {
        result = (result * i) % mod;
    }
    return result;
}

int first_natural_with_factorial_divisible(unsigned long long x) {
    if (x <= 1) {
        return 1;
    }

    unsigned long long max_check = 1000;
    for (unsigned long long i = 1; i <= max_check; i++) {
        if (factorial_mod(i, x) == 0) {
            return (int)i;
        }
    }
    
    return -1;
}

int main(void) {
    unsigned long long test_values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 15, 20, 24, 25, 30, 100, 120, 720, 1000};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        int result = first_natural_with_factorial_divisible(test_values[i]);
        printf("x = %llu: %d\n", test_values[i], result);
    }
    
    return 0;
}