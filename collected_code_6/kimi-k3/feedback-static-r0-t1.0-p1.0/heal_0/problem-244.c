#include <stdio.h>
#include <math.h>
#include <limits.h>

long long next_perfect_square(long long num) {
    if (num < 0) {
        return 0;
    }
    
    if (num >= LLONG_MAX - 1) {
        return -1;
    }
    
    long long root = (long long)sqrt((double)num);
    
    if (root > LLONG_MAX / (root + 1) - 1) {
        return -1;
    }
    
    long long next_root = root + 1;
    long long result = next_root * next_root;
    
    if (result <= num) {
        next_root++;
        if (next_root > LLONG_MAX / next_root) {
            return -1;
        }
        result = next_root * next_root;
    }
    
    return result;
}

int main(void) {
    long long test_cases[] = {0, 1, 15, 16, 17, 100, LLONG_MAX - 1};
    size_t num_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (size_t i = 0; i < num_cases; i++) {
        long long result = next_perfect_square(test_cases[i]);
        if (result == -1) {
            printf("Input: %lld -> Overflow occurred\n", test_cases[i]);
        } else {
            printf("Input: %lld -> Next perfect square: %lld\n", test_cases[i], result);
        }
    }
    
    return 0;
}