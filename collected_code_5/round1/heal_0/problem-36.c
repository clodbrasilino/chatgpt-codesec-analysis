#include <stdio.h>

int findNthDigitOfFraction(int numerator, int denominator, int nthDigit) {
    if (denominator == 0 || nthDigit < 0) {
        return -1;
    }

    // Convert the fraction into decimal form
    double fraction = (double)numerator / denominator;

    int digit;
    for (int i = 0; i <= nthDigit; i++) {
        fraction *= 10;
        digit = (int)fraction % 10;
    }

    return digit;
}

int main() {
    int numerator, denominator, nthDigit;

    printf("Enter numerator: ");
    scanf("%d", &numerator);
    printf("Enter denominator: ");
    scanf("%d", &denominator);
    printf("Enter the nth digit you want to find: ");
    scanf("%d", &nthDigit);

    int result = findNthDigitOfFraction(numerator, denominator, nthDigit);

    if (result == -1) {
        printf("Invalid input\n");
    } else {
        printf("The %dth digit in the decimal representation of %d/%d is %d\n", nthDigit, numerator, denominator, result);
    }

    return 0;
}