#include <stdio.h>

long long multiply(int a, int b);

long long multiply(int a, int b) {
    long long result = 0;
    long long abs_a = a;
    long long abs_b = b;
    int is_negative = 0;

    if (abs_a < 0) {
        abs_a = -abs_a;
        is_negative = !is_negative;
    }
    
    if (abs_b < 0) {
        abs_b = -abs_b;
        is_negative = !is_negative;
    }

    while (abs_b > 0) {
        if (abs_b & 1) {
            result += abs_a;
        }
        abs_a <<= 1;
        abs_b >>= 1;
    }

    if (is_negative) {
        result = -result;
    }

    return result;
}

int main(void) {
    int x = 12345;
    int y = -67890;
    long long product = multiply(x, y);
    
    printf("%lld\n", product);
    
    return 0;
}