#include <stdio.h>

int findRemainder(int num1, int num2) {
    int remainder = num1 % num2;
    return remainder;
}

int main() {
    int num1, num2;

    printf("Enter first number: ");
    scanf("%d", &num1);

    printf("Enter second number: ");
    scanf("%d", &num2);

    int remainder = findRemainder(num1, num2);
    printf("Remainder: %d\n", remainder);

    return 0;
}