#include <stdio.h>

int multiply(int a, int b) {
    int result = 0;
    while (b > 0) {
        if (b % 2 == 1)
            result = result + a;
        a = a << 1;
        b = b >> 1;
    }
    return result;
}

int main() {
    int num1, num2;
    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);
    printf("Product: %d", multiply(num1, num2));
    return 0;
}