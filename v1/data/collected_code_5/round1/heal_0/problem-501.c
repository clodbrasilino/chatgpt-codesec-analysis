#include <stdio.h>

int findCommonDivisor(int a, int b) {
    while(a != b) {
        if(a > b) {
            a -= b;
        } else {
            b -= a;
        }
    }

    return a;
}

int main(void) {
    int num1, num2;

    printf("Enter first number: ");
    scanf("%d", &num1);

    printf("Enter second number: ");
    scanf("%d", &num2);

    if(num1 < 1 || num2 < 1) {
        printf("Invalid input. Numbers must be greater than 0.\n");
        return 1;
    }

    printf("The greatest common divisor is: %d\n", findCommonDivisor(num1, num2));

    return 0;
}