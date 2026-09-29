#include <stdio.h>

int multiply(int a, int b) {
    int result = 0;
    int positive = 1;
    
    if (b < 0) {
        positive = -positive;
        b = -b;
    }
    
    while (b > 0) {
        if (b & 1) {
            result += a;
        }
        a <<= 1;
        b >>= 1;
    }
    
    return positive * result;
}

int main() {
    int a = 5;
    int b = -3;
    printf("%d * %d = %d\n", a, b, multiply(a, b));
    return 0;
}