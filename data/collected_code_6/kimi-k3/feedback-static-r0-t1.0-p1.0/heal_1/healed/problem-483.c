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

int find_first_factorial_divisible(unsigned long long x) {
    if (x == 0) {
        return -1;
    }
    if (x == 1) {
        return 1;
    }
    
    unsigned long long factorial = 1;
    int n = 1;
    
    while (1) {
        factorial *= (unsigned long long)n;
        
        if (factorial % x == 0) {
            return n;
        }
        
        if (factorial > ULLONG_MAX / (unsigned long long)(n + 1)) {
            unsigned long long temp_x = x;
            for (int i = 2; i <= n + 1; i++) {
                unsigned long long temp_i = (unsigned long long)i;
                unsigned long long common = gcd(temp_i, temp_x);
                temp_x /= common;
                if (temp_x == 1) {
                    return i;
                }
            }
            if (temp_x > 1) {
                return -1;
            }
        }
        
        n++;
    }
}

int main(void) {
    unsigned long long x;
    
    if (scanf("%llu", &x) != 1) {
        return 1;
    }
    
    int result = find_first_factorial_divisible(x);
    
    if (result == -1) {
        printf("-1\n");
    } else {
        printf("%d\n", result);
    }
    
    return 0;
}