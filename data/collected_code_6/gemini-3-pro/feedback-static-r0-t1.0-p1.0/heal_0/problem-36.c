#include <stdio.h>
#include <stdlib.h>

int findNthDigit(int numerator, int denominator, int n) {
    if (denominator == 0 || n <= 0) {
        return -1;
    }

    numerator = abs(numerator);
    denominator = abs(denominator);

    numerator = numerator % denominator;

    int current_digit = 0;
    for (int i = 0; i < n; i++) {
        numerator *= 10;
        current_digit = numerator / denominator;
        numerator = numerator % denominator;
    }

    return current_digit;
}

int main(void) {
    int num = 1;
    int den = 7;
    int n = 3;

    int digit = findNthDigit(num, den, n);

    if (digit != -1) {
        printf("The %dth digit of %d/%d is %d\n", n, num, den, digit);
    } else {
        printf("Invalid input or division by zero.\n");
    }

    return 0;
}