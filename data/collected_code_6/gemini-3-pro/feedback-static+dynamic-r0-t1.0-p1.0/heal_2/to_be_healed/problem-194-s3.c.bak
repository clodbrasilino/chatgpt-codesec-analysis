#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int octalToDecimal(long long octalNumber) {
    int decimalNumber = 0;
    int i = 0;
    long long temp = octalNumber;

    if (octalNumber < 0) {
        return -1; 
    }

    while (temp != 0) {
        int remainder = temp % 10;
        
        if (remainder >= 8) {
            return -1; 
        }
        
        /* Possible weaknesses found:
         * UBSan: 3.6814e+09 is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000000,time:409,execs:224,op:havoc,rep:4)
         */
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