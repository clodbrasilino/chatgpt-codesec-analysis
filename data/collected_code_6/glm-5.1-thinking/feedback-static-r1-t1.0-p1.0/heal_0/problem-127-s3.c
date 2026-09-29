#include <stdio.h>
#include <limits.h>

int multiply(int a, int b) {
    long long la = a;
    long long lb = b;
    long long result = 0;

    if (la < 0) {
        la = -la;
        lb = -lb;
    }

    while (la > 0) {
        if (la & 1) {
            result += lb;
        }
        la >>= 1;
        lb <<= 1;
    }

    if (result > INT_MAX) {
        return INT_MAX;
    }
    if (result < INT_MIN) {
        return INT_MIN;
    }
    
    return (int)result;
}

int main(void) {
    printf("%d\n", multiply(5, 6));
    printf("%d\n", multiply(-5, 6));
    printf("%d\n", multiply(0, 6));
    printf("%d\n", multiply(INT_MIN, -1));
    printf("%d\n", multiply(INT_MAX, 2));
    return 0;
}