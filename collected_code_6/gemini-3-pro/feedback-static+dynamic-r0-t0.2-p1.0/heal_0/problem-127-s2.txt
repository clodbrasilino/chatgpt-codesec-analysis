#include <stdio.h>
#include <stdlib.h>

long long multiply(int a, int b) {
    long long result = 0;
    long long la = a;
    long long lb = b;
    int is_negative = 0;

    if (la < 0) {
        la = -la;
        is_negative = !is_negative;
    }
    if (lb < 0) {
        lb = -lb;
        is_negative = !is_negative;
    }

    while (lb > 0) {
        if (lb & 1) {
            result += la;
        }
        la <<= 1;
        lb >>= 1;
    }

    return is_negative ? -result : result;
}

int main(void) {
    int num1 = 15;
    int num2 = -4;
    
    long long result = multiply(num1, num2);
    
    printf("%lld\n", result);
    
    return 0;
}