#include <stdio.h>
#include <limits.h>

unsigned long long sum_of_squares_of_odds(unsigned int n) {
    unsigned long long sum = 0;
    unsigned long long odd = 1;
    
    for (unsigned int i = 0; i < n; ++i) {
        if (sum > ULLONG_MAX - (odd * odd)) {
            return 0;
        }
        sum += odd * odd;
        odd += 2;
    }
    
    return sum;
}

int main(void) {
    unsigned int n;
    
    if (scanf("%u", &n) != 1) {
        return 1;
    }
    
    unsigned long long result = sum_of_squares_of_odds(n);
    
    if (result == 0 && n > 0) {
        return 1;
    }
    
    printf("%llu\n", result);
    
    return 0;
}