#include <stdio.h>
#include <stdlib.h>

int nth_digit_of_fraction(int numerator, int denominator, int n) {
    if (denominator == 0) {
        return -1;
    }
    if (numerator < 0 || denominator < 0 || n < 1) {
        return -1;
    }
    if (numerator >= denominator) {
        numerator %= denominator;
    }
    for (int i = 0; i < n; i++) {
        numerator *= 10;
        int digit = numerator / denominator;
        numerator %= denominator;
        if (i == n - 1) {
            return digit;
        }
    }
    return -1;
}

int main(void) {
    int numerator, denominator, n;
    printf("Enter numerator: ");
    if (scanf("%d", &numerator) != 1) {
        return 1;
    }
    printf("Enter denominator: ");
    if (scanf("%d", &denominator) != 1) {
        return 1;
    }
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    int result = nth_digit_of_fraction(numerator, denominator, n);
    if (result == -1) {
        printf("Invalid input\n");
    } else {
        printf("The %d-th digit is: %d\n", n, result);
    }
    return 0;
}