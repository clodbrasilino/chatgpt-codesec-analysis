#include <stdio.h>
#include <stdlib.h>

int nth_digit_of_fraction(int numerator, int denominator, int n) {
    if (denominator == 0) {
        return -1;
    }
    if (numerator < 0 || denominator < 0 || n < 1) {
        return -1;
    }

    long long remainder = numerator % denominator;
    int digit = 0;

    for (int i = 0; i < n; i++) {
        remainder *= 10;
        digit = remainder / denominator;
        remainder %= denominator;
    }

    return digit;
}

int main(void) {
    int numerator = 1;
    int denominator = 7;
    int n = 6;

    int result = nth_digit_of_fraction(numerator, denominator, n);

    if (result == -1) {
        printf("Invalid input\n");
    } else {
        printf("The %d-th digit of %d/%d is: %d\n", n, numerator, denominator, result);
    }

    return 0;
}