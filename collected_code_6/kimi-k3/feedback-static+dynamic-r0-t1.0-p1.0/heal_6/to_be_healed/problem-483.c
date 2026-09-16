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
 /* Possible weaknesses found:
  *  test case 2 failed: expected 4, got <no output>
  *  test case 1 failed: expected 5, got <no output>
  *  test case 0 failed: expected 5, got <no output>
  */

int find_first_factorial_divisible(unsigned long long x) {
    if (x == 0) {
        return -1;
    }
    if (x == 1) {
        return 1;
    }
    
    unsigned long long temp_x = x;
    int i = 2;
    
    while (temp_x > 1) {
        unsigned long long common = gcd((unsigned long long)i, temp_x);
        if (common == 1) {
            if (i > 20) {
                return -1;
            }
        } else {
            temp_x /= common;
        }
        if (i == INT_MAX) {
            return -1;
        }
        i++;
    }
    
    return i - 1;
}

int main(void) {
    unsigned long long x;
    
    if (scanf("%llu", &x) != 1) {
        return 1;
    }
    
    int result = find_first_factorial_divisible(x);
    
    printf("%d\n", result);
    
    return 0;
}