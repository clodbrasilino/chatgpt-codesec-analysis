#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>

bool next_perfect_square(long long n, long long *result) {
    if (result == NULL) {
        return false;
    }
    
    if (n < 0) {
        *result = 0;
        return true;
    }
    
    if (n >= LLONG_MAX - 1) {
        return false;
    }
    
    long long next_val = n + 1;
    long long low = 0;
    long long high = next_val;
    long long root = 0;
    
    while (low <= high) {
        long long mid = low + (high - low) / 2;
        long long square;
        
        if (mid != 0 && mid > LLONG_MAX / mid) {
            high = mid - 1;
            continue;
        }
        
        square = mid * mid;
        
        if (square == next_val) {
            *result = square;
            return true;
        }
        
        if (square < next_val) {
            root = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    
    if (root == 0 && next_val > 1) {
        return false;
    }
    
    long long next_root = root + 1;
    
    if (next_root > 0 && next_root <= LLONG_MAX / next_root) {
        *result = next_root * next_root;
        return true;
    }
    
    return false;
}

int main(void) {
    long long number;
    long long result;
    
    printf("Enter a number: ");
    if (scanf("%lld", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (next_perfect_square(number, &result)) {
        printf("Next perfect square: %lld\n", result);
    } else {
        printf("No perfect square found within representable range\n");
    }
    
    return 0;
}