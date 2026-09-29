#include <stdio.h>
#include <string.h>

int checkDecimalPrecision(float num) {
    int decimalCount = 0;
    int decimalIndex = -1;
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[65];
    int len;

    len = snprintf(str, sizeof(str), "%.2f", num);

    for (int i = 0; i < len; i++) {
        if (str[i] == '.') {
            decimalIndex = i;
        } else if (decimalIndex != -1 && str[i] >= '0' && str[i] <= '9') {
            decimalCount++;
        }
    }

    return (decimalCount == 2) ? 1 : 0;
}

int main() {
    float num = 0;

    printf("Enter a decimal number: ");
    scanf("%f", &num);

    if (checkDecimalPrecision(num)) {
        printf("Decimal number has a precision of 2.\n");
    } else {
        printf("Decimal number does not have a precision of 2.\n");
    }

    return 0;
}