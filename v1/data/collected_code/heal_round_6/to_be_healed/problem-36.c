#include<stdio.h>
#include<string.h>

#define MAX_BUF_SIZE 51

int findNthDigit(int numerator, int denominator, int n) {

    if (numerator <= 0 || denominator <= 0) {
        printf("Invalid inputs. Numerator and denominator must be positive integers.");
        return -1;
    }

    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char fractionString[MAX_BUF_SIZE];
    
    int integerPart = numerator / denominator;
    int remainder = numerator % denominator;
    double properFraction = (double)remainder / denominator;

    snprintf(fractionString, sizeof(fractionString) - 1, "%.45f", properFraction);

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int length = strlen(fractionString);

    if (n < 0 || n >= length - 2) { // Substract 2 from length to compensate for decimal before fraction and null character at the end
        printf("Invalid position, must be between 0 and length of the string - 2");
        return -1;
    }

    int digit = fractionString[n+2] - '0'; // n+2 to ignore decimal point and get nth digit of fraction
    
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