#include <stdio.h>

int checkDecimalPrecision(float num) {
    int decimalCount = 0;
    int decimalIndex = -1;

    char str[50]; // assuming maximum 50 characters

    sprintf(str, "%f", num);

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '.') {
            decimalIndex = i;
        } else if (decimalIndex != -1 && str[i] >= '0' && str[i] <= '9') {
            decimalCount++;
        }
    }

    return (decimalCount == 2) ? 1 : 0;
}

int main() {
    float num;

    printf("Enter a decimal number: ");
    scanf("%f", &num);

    if (checkDecimalPrecision(num)) {
        printf("Decimal number has a precision of 2.\n");
    } else {
        printf("Decimal number does not have a precision of 2.\n");
    }

    return 0;
}