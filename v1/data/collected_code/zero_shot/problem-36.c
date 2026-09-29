#include<stdio.h>

int findNthDigit(int numerator, int denominator, int n) {
    // Check if the numbers are positive
    if (numerator <= 0 || denominator <= 0) {
        printf("Invalid inputs. Numerator and denominator must be positive integers.");
        return -1;
    }
    
    // Calculate the proper fraction value
    int integerPart = numerator / denominator;
    int remainder = numerator % denominator;
    double properFraction = (double)remainder / denominator;
    
    // Convert the proper fraction value to string
    char fractionString[20];
    sprintf(fractionString, "%.15f", properFraction);
    
    // Find the nth digit in the proper fraction
    int digit = fractionString[n] - '0';
    
    return digit;
}

int main() {
    int numerator, denominator, n;
    printf("Enter numerator: ");
    scanf("%d", &numerator);
    printf("Enter denominator: ");
    scanf("%d", &denominator);
    printf("Enter the position of the digit to find: ");
    scanf("%d", &n);
    
    int nthDigit = findNthDigit(numerator, denominator, n);
    
    if (nthDigit != -1) {
        printf("The %dth digit in the proper fraction of %d/%d is %d", n, numerator, denominator, nthDigit);
    }
    
    return 0;
}