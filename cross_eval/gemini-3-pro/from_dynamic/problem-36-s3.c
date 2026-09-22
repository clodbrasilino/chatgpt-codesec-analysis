#include <stdio.h>
#include <stdlib.h>

int findNthDigit(int numerator, int denominator, int n) {
    if (denominator == 0 || n <= 0) {
        return -1; 
    }

    numerator = abs(numerator);
    denominator = abs(denominator);

    numerator = numerator % denominator;

    int digit = -1;
    for (int i = 0; i < n; i++) {
        numerator *= 10;
        digit = numerator / denominator;
        numerator = numerator % denominator;
    }

    return digit;
}

int main(void) {
    int numerator = 1;
    int denominator = 2;
    int n = 1;

    int result = findNthDigit(numerator, denominator, n);
    if (result != -1) {
        printf("%d\n", result);
    } else {
        printf("Invalid input or calculation error.\n");
    }

    numerator = 22;
    denominator = 7;
    n = 5;

    result = findNthDigit(numerator, denominator, n);
    if (result != -1) {
        printf("%d\n", result);
    } else {
        printf("Invalid input or calculation error.\n");
    }

    return 0;
}