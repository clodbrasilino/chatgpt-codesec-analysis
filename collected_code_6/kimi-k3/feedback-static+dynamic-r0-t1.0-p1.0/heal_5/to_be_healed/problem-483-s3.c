#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

bool is_factorial_divisible(uint64_t n, uint64_t x) {
    if (x == 0) {
        return false;
    }
    if (x == 1) {
        return true;
    }
    
    uint64_t remainder = 1;
    uint64_t i;
    
    for (i = 2; i <= n; i++) {
        uint64_t factor = i % x;
        if (factor == 0) {
            return true;
        }
        if (remainder > UINT64_MAX / factor) {
            uint64_t gcd_val = remainder;
            uint64_t temp = x;
            while (temp != 0) {
                uint64_t t = temp;
                temp = gcd_val % temp;
                gcd_val = t;
            }
            remainder = remainder / gcd_val;
            uint64_t x_reduced = x / gcd_val;
            if (x_reduced == 0) {
                return true;
            }
            if (remainder > UINT64_MAX / factor) {
                return false;
            }
            remainder = (remainder * factor) % x_reduced;
            if (remainder == 0) {
                return true;
            }
            remainder = (remainder * gcd_val) % x;
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    uint64_t x;
    
    printf("Enter the value of x: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    size_t len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
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