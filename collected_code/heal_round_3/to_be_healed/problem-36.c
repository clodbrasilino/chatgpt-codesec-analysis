#include<stdio.h>
#include<string.h>

int findNthDigit(int numerator, int denominator, int n) {
    if (numerator <= 0 || denominator <= 0) {
        printf("Invalid inputs. Numerator and denominator must be positive integers.");
        return -1;
    }
    
    int integerPart = numerator / denominator;
    int remainder = numerator % denominator;
    double properFraction = (double)remainder / denominator;
    
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char fractionString[50];
    snprintf(fractionString, 50, "%.45f", properFraction);

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    if (n < 0 || n >= strlen(fractionString)) {
        printf("Invalid position, must be between 0 and lenght of the string");
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
        printf("The %dth digit in the proper fraction of %d/%d is %d", n, numerator, denominator, nthDigit);
    }
    
    return 0;
}