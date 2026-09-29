#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

bool is_prime(unsigned long long n) {
    if (n <= 1) {
        return false;
    }
    if (n <= 3) {
        return true;
    }
    if (n % 2 == 0 || n % 3 == 0) {
        return false;
    }
    for (unsigned long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

unsigned long long nth_nsw_prime(unsigned int n) {
    if (n == 0) {
        return 0;
    }
    
    unsigned int count = 0;
    unsigned long long s0 = 1;
    unsigned long long s1 = 1;
    unsigned int k = 1;

    while (1) {
        k++;
        
        if (ULLONG_MAX / 2 < s1) {
            return 0;
        }
        unsigned long long double_s1 = 2 * s1;
        
        if (ULLONG_MAX - double_s1 < s0) {
            return 0;
        }
        unsigned long long s2 = double_s1 + s0;
        
        if (k % 2 != 0) {
            if (is_prime(s2)) {
                count++;
                if (count == n) {
                    return s2;
                }
            }
        }
        
        s0 = s1;
        s1 = s2;
    }
    
    return 0;
}

int main(void) {
    unsigned int n = 4;
    unsigned long long result = nth_nsw_prime(n);
    
    if (result == 0) {
        fprintf(stderr, "Error: Overflow occurred or invalid input.\n");
        return EXIT_FAILURE;
    }
    
    printf("%llu\n", result);
    
    return EXIT_SUCCESS;
}