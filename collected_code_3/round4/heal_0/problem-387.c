#include <stdio.h>
#include <stdlib.h>

int checkEvenOddHex(char *hex) {
    int len = strlen(hex);
    int lastDigit = hex[len - 1] - '0';

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