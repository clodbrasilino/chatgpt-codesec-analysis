#include <stdio.h>

int decimalToOctal(int decimalNum) {
    int octalNum = 0, i = 1;

    while (decimalNum != 0) {
        octalNum += (decimalNum % 8) * i;
        decimalNum /= 8;
        i *= 10;
    }

    return octalNum;
}

int main() {
    int decimalNum;

    printf("Enter a Decimal Number: ");
    scanf("%d", &decimalNum);

    printf("Octal Number: %d", decimalToOctal(decimalNum));

    return 0;
}