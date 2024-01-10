#include<stdio.h>
#include<string.h>

#define MAX_BUF_SIZE 51

int findNthDigit(int numerator, int denominator, int n) {
    if (numerator <= 0 || denominator <= 0) {
        printf("Invalid inputs. Numerator and denominator must be positive integers.");
        return -1;
    }

    char fractionString[MAX_BUF_SIZE];
    int integerPart = numerator / denominator;
    int remainder = numerator % denominator;
    double properFraction = (double)remainder / denominator;

    snprintf(fractionString, sizeof(fractionString), "%.45f", properFraction);
    int length = strnlen(fractionString, MAX_BUF_SIZE - 1);

    if (n < 0 || n >= length) {
        printf("Invalid position, must be between 0 and length of the string");
        return -1;
    }

    int digit = fractionString[n] - '0';
    
    return digit;
}

int main() {
    int numerator = 0, denominator = 0, n = 0;
    printf("Enter numerator: ");
    scanf("%d", &numerator);
    printf("Enter denominator: ");
    scanf("%d", &denominator);
    printf("Enter the position of the digit to find: ");
    scanf("%d", &n);

    int nthDigit = findNthDigit(numerator, denominator, n);
    
    if (nthDigit != -1) {
        printf("The %dth digit in the proper fraction of %d/%d is %d\n", n, numerator, denominator, nthDigit);
    }
    
    return 0;
}