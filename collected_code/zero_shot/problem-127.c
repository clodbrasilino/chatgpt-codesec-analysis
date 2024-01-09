#include <stdio.h>

int multiply(int num1, int num2) {
    int result = 0;

    if (num1 == 0 || num2 == 0) {
        return 0;
    }

    int sign = ((num1 < 0) ^ (num2 < 0)) ? -1 : 1;

    num1 = abs(num1);
    num2 = abs(num2);

    while (num2 > 0) {
        if (num2 & 1) {
            result += num1;
        }

        num1 <<= 1;
        num2 >>= 1;
    }

    return sign * result;
}

int main() {
    int num1, num2;

    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);

    int result = multiply(num1, num2);

    printf("Result: %d\n", result);

    return 0;
}