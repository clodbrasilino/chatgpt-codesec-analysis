#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long multiply(int a, int b) {
    long long result = 0;
    long long abs_a = llabs((long long)a);
    long long abs_b = llabs((long long)b);
    
    while (abs_b > 0) {
        if (abs_b & 1) {
            result += abs_a;
        }
        abs_a <<= 1;
        abs_b >>= 1;
    }
    
    if ((a < 0 && b > 0) || (a > 0 && b < 0)) {
        result = -result;
    }
    
    return result;
}

int main(void) {
    int num1 = 15;
    int num2 = -4;
    
    long long result = multiply(num1, num2);
    
    printf("%lld\n", result);
    
    return 0;
}