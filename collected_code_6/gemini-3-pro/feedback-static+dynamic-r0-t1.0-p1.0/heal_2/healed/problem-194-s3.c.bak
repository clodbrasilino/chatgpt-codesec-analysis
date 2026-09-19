#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int octalToDecimal(long long octalNumber) {
    long long decimalNumber = 0;
    long long multiplier = 1;
    long long temp = octalNumber;

    if (octalNumber < 0) {
        return -1; 
    }

    while (temp != 0) {
        int remainder = temp % 10;
        
        if (remainder >= 8) {
            return -1; 
        }
        
        decimalNumber += remainder * multiplier;
        if (decimalNumber > INT_MAX) {
            return -1;
        }
        
        temp /= 10;
        if (temp != 0) {
            if (multiplier > (LLONG_MAX / 8)) {
                return -1;
            }
            multiplier *= 8;
        }
    }

    return (int)decimalNumber;
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