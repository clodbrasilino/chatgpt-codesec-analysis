#include <stdio.h>
#include <stdlib.h>

int nth_digit_proper_fraction(long numerator, long denominator, int n) {
    long long result = 1;
    for (int i = 0; i < n; ++i) {
        if (denominator > 0 && result * 10 % denominator == 0)
            return 0;
        result = (result * 10) % denominator;
    }
    return (10 * result / denominator) % 10;
}

int main() {
    long num, den;
    int n;

    printf("Enter the numerator: ");
    if (scanf("%ld", &num) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Enter the denominator: ");
    if (scanf("%ld", &den) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    if (den <= 0) {
        printf("Denominator must be greater than 0.\n");
        return 1;
    }

    printf("Enter the digit position (n): ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    if (n < 0) {
        printf("n must be a non-negative integer.\n");
        return 1;
    }

    int digit = nth_digit_proper_fraction(num, den, n);
    printf("The %dth digit in the proper fraction of %ld/%ld is: %d\n", n, num, den, digit);

    return 0;
}