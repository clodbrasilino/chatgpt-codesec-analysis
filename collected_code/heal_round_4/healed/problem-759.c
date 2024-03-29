#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkDecimalPrecision(float num) {
    int decimalCount = 0;
    int decimalIndex = -1;
    char* str = NULL;
    int len;

    len = snprintf(NULL, 0, "%.2f", num);

    if (len > 0) {
        str = malloc((len + 1) * sizeof(char));
        if (str != NULL) {
            snprintf(str, len + 1, "%.2f", num);

            for (int i = 0; i < len; i++) {
                if (str[i] == '.') {
                    decimalIndex = i;
                } else if (decimalIndex != -1 && str[i] >= '0' && str[i] <= '9') {
                    decimalCount++;
                }
            }

            free(str);
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