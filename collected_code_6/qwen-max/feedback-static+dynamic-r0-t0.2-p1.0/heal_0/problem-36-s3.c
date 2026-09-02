#include <stdio.h>
#include <stdlib.h>

int nth_digit_proper_fraction(int numerator, int denominator, int n) {
    if (n <= 0 || denominator == 0) return -1;
    long long result = 0;
    for (int i = 0; i < n; ++i) {
        numerator *= 10;
        result = numerator / denominator;
        numerator %= denominator;
    }
    return result % 10;
}

int main() {
    int num, den, pos;
    printf("Enter the numerator, denominator, and the position of the digit: ");
    if (scanf("%d %d %d", &num, &den, &pos) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    int digit = nth_digit_proper_fraction(num, den, pos);
    if (digit == -1) {
        fprintf(stderr, "Error: Invalid position or denominator is zero\n");
        return EXIT_FAILURE;
    }
    printf("The %dth digit is: %d\n", pos, digit);
    return EXIT_SUCCESS;
}