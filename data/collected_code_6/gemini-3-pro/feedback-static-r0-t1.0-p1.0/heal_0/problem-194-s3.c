#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int octalToDecimal(long long octalNumber) {
    int decimalNumber = 0;
    int i = 0;
    int remainder;
    long long temp = octalNumber;

    if (octalNumber < 0) {
        return -1; 
    }

    while (temp != 0) {
        remainder = temp % 10;
        
        if (remainder >= 8) {
            return -1; 
        }
        
        decimalNumber += remainder * pow(8, i);
        ++i;
        temp /= 10;
    }

    return decimalNumber;
}

int main(void) {
    long long octalNumber;
    int decimalNumber;

    if (scanf("%lld", &octalNumber) != 1) {
        return EXIT_FAILURE;
    }

    decimalNumber = octalToDecimal(octalNumber);

    if (decimalNumber == -1) {
        return EXIT_FAILURE;
    }

    printf("%d\n", decimalNumber);

    return EXIT_SUCCESS;
}