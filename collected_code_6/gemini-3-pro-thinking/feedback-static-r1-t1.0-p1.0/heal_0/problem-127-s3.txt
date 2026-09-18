#include <stdio.h>

long long multiply(int a, int b) {
    long long num1 = (long long)a;
    long long num2 = (long long)b;
    long long result = 0;
    int is_negative = 0;

    if (num1 < 0) {
        is_negative = !is_negative;
        num1 = -num1;
    }
    
    if (num2 < 0) {
        is_negative = !is_negative;
        num2 = -num2;
    }

    while (num2 > 0) {
        if (num2 & 1) {
            result += num1;
        }
        num1 <<= 1;
        num2 >>= 1;
    }

    if (is_negative) {
        result = -result;
    }

    return result;
}

int main(void) {
    int val1 = 45;
    int val2 = -324;
    long long result = multiply(val1, val2);
    
    printf("%lld\n", result);
    
    return 0;
}