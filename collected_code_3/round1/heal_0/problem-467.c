#include <stdio.h>

int decimalToOctal(int decimal) {
    int octal = 0, i = 1;

    while (decimal != 0) {
        octal += (decimal % 8) * i;
        decimal /= 8;
        i *= 10;
    }

    return octal;
}

int main() {
    int decimal;

    printf("Enter a decimal number: ");
    scanf("%d", &decimal);

    printf("Octal of the decimal number %d is: %d", decimal, decimalToOctal(decimal));

    return 0;
}