#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#define BUFFER_SIZE 64

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
            uint64_t rem_red = remainder / g;
            uint64_t x_red = x / g;
            
            if (x_red == 0) {
                return true;
            }
            
            if (rem_red > UINT64_MAX / factor) {
                return false;
            }
            
            remainder = (rem_red * factor) % x_red;
            if (remainder == 0) {
                return true;
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
    
    uint64_t n = 1;
    
    while (n < UINT64_MAX) {
        if (is_factorial_divisible(n, x)) {
            return n;
        }
        n++;
    }
    
    return UINT64_MAX;
}

int main(void) {
    char buffer[BUFFER_SIZE];
    uint64_t x;
    
    printf("Enter the value of x: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    size_t len = strnlen(buffer, sizeof(buffer));
    if (len == 0 || len >= sizeof(buffer)) {
        return 1;
    }
    
    if (buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }
    
    if (len == 0) {
        return 1;
    }
    
    errno = 0;
    char *endptr;
    unsigned long long val = strtoull(buffer, &endptr, 10);
    
    if (errno != 0 || endptr == buffer || *endptr != '\0') {
        return 1;
    }
    
    x = (uint64_t)val;
    
    uint64_t result = find_first_natural_number(x);
    
    printf("The first natural number whose factorial is divisible by %" PRIu64 " is %" PRIu64 ".\n", x, result);
    
    return 0;
}