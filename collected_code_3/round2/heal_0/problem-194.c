#include <stdio.h>
#include <math.h>

int octalToDecimal(int octalNumber) {
    int decimalNumber = 0, i = 0, remainder;
    while (octalNumber != 0) {
        remainder = octalNumber % 10;
        octalNumber /= 10;
        decimalNumber += remainder * pow(8, i);
        ++i;
    }
    return decimalNumber;
}

int main() {
    int octalNumber;
    printf("Enter an Octal Number: ");
    scanf("%d", &octalNumber);
    printf("Equivalent Decimal Number is: %d", octalToDecimal(octalNumber));
    return 0;
}