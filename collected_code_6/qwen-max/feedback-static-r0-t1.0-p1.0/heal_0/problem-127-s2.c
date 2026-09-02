#include <stdio.h>
#include <limits.h>

int multiply(int x, int y) {
    int result = 0;
    int negativeResult = 0;
    if (y < 0) {
        y = -y;
        negativeResult = 1;
    }
    while (y > 0) {
        if (y & 1) {
            result = result + x;
        }
        x <<= 1;
        y >>= 1;
    }
    if (negativeResult) {
        result = -result;
    }
    return result;
}

int main() {
    int a, b;
    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);
    int product = multiply(a, b);
    printf("Product: %d\n", product);
    return 0;
}