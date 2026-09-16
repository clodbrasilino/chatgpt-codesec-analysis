#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    while (b != 0) {
        unsigned long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int find_pair(unsigned long long low, unsigned long long high, unsigned long long *num1, unsigned long long *num2) {
    if (low == 0 || low > high || num1 == NULL || num2 == NULL) {
        return 0;
    }

    for (unsigned long long i = 1; i <= high / 2; i++) {
        if (high / i < 2) {
            break;
        }
        
        unsigned long long max_multiplier = high / i;
        unsigned long long min_multiplier = (low + i - 1) / i;
        
        if (min_multiplier < 2) {
            min_multiplier = 2;
        }
        
        if (min_multiplier <= max_multiplier) {
            unsigned long long j = i * min_multiplier;
            
            if (j > i && j <= high) {
                unsigned long long g = gcd(i, j);
                unsigned long long lcm_val = (i / g) * j;
                
                if (lcm_val >= low && lcm_val <= high) {
                    *num1 = i;
                    *num2 = j;
                    return 1;
                }
            }
        }
    }
    
    return 0;
}

int main(void) {
    unsigned long long low, high;
    unsigned long long num1, num2;
    
    if (scanf("%llu %llu", &low, &high) != 2) {
        return EXIT_FAILURE;
    }
    
    if (find_pair(low, high, &num1, &num2)) {
        printf("%llu %llu\n", num1, num2);
    } else {
        printf("No solution\n");
    }
    
    return EXIT_SUCCESS;
}