#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkEvenOddHex(char *hex) {
    int len = strlen(hex);
    int lastDigit;
    if (hex[len - 1] > '9')
        lastDigit = hex[len - 1] - 'A' + 10;
    else
        lastDigit = hex[len - 1] - '0';

    if (lastDigit % 2 == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    char hex[100];
    printf("Enter a hexadecimal number: ");
    scanf("%s", hex);

    int result = checkEvenOddHex(hex);

    if (result == 1) {
        printf("The hexadecimal number is even.\n");
    } else {
        printf("The hexadecimal number is odd.\n");
    }

    return 0;
}