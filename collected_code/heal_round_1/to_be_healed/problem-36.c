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
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char fractionString[20];
    /* Possible weaknesses found:
     *   Does not check for buffer overflows (CWE-120). Use sprintf_s, snprintf, or  vsnprintf. Risk is low because the source has a constant maximum length.
     *  Cannot determine that 'fractionString[0]' is initialized [premium-bughuntingUninit]
     */
    sprintf(fractionString, "%.15f", properFraction);
    
    // Find the nth digit in the proper fraction
    int digit = fractionString[n] - '0';
    
    return digit;
}

int main() {
    int numerator, denominator, n;
    printf("Enter numerator: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'numerator' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &numerator);
    printf("Enter denominator: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'denominator' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &denominator);
    printf("Enter the position of the digit to find: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &n);
    
    int nthDigit = findNthDigit(numerator, denominator, n);
    
    if (nthDigit != -1) {
        printf("The %dth digit in the proper fraction of %d/%d is %d", n, numerator, denominator, nthDigit);
    }
    
    return 0;
}