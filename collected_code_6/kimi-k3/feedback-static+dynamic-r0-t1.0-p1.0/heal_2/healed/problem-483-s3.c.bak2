#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>

uint64_t gcd_u64(uint64_t a, uint64_t b) {
    while (b != 0) {
        uint64_t t = b;
        b = a % b;
        a = t;
    }
    return a;
}

bool is_factorial_divisible(uint64_t n, uint64_t x) {
    if (x == 0) {
        return false;
    }
    if (x == 1) {
        return true;
    }
    
    uint64_t remainder = 1;
    
    for (uint64_t i = 2; i <= n; i++) {
        uint64_t factor = i % x;
        
        if (factor == 0) {
            return true;
        }
        
        if (remainder > UINT64_MAX / factor) {
            uint64_t g = gcd_u64(remainder, x);
            uint64_t rem_reduced = remainder / g;
            uint64_t x_reduced = x / g;
            
            if (rem_reduced > UINT64_MAX / factor) {
                return false;
            }
            
            remainder = (rem_reduced * factor) % x_reduced;
            
            if (remainder == 0) {
                return true;
            }
            
            if (remainder > UINT64_MAX / g) {
                return false;
            }
            
            remainder = (remainder * g) % x;
        } else {
            remainder = (remainder * factor) % x;
        }
        
        if (remainder == 0) {
            return true;
        }
    }
    
    return false;
}

uint64_t find_first_natural_number(uint64_t x) {
    if (x == 0) {
        return 0;
    }
    if (x == 1) {
        return 1;
    }
    
    for (uint64_t n = 1; n < UINT64_MAX; n++) {
        if (is_factorial_divisible(n, x)) {
            return n;
        }
    }
    
    return 0;
}

int main(void) {
    uint64_t x;
    
    printf("Enter the value of x: ");
    if (scanf("%" SCNu64, &x) != 1) {
        return 1;
    }
    
    uint64_t result = find_first_natural_number(x);
    
    printf("The first natural number whose factorial is divisible by %" PRIu64 " is %" PRIu64 ".\n", x, result);
    
    return 0;
}