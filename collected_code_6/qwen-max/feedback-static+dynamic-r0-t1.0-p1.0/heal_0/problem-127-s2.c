#include <stdio.h>

int multiply(int a, int b) {
    int result = 0;
    while (b != 0) {
        if (b & 1) {
            result += a;
        }
        a <<= 1;
        b >>= 1;
    }
    return result;
}

int main() {
    int x = 5, y = 3;
    printf("The product of %d and %d is %d\n", x, y, multiply(x, y));
    return 0;
}