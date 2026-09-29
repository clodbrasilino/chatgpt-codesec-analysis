#include <stdio.h>

int multiply(int a, int b) {
    int result = 0;
    int multiplier = (b < 0) ? -1 : 1;
    while (b != 0) {
        if (b & 1) {
            result += a * multiplier;
        }
        a <<= 1;
        b >>= 1;
    }
    return result;
}

int main() {
    int a = 5;
    int b = 6;
    printf("%d * %d = %d\n", a, b, multiply(a, b));
    return 0;
}