#include <stdio.h>
#include <string.h>

int binaryToInteger(char *binary) {
    int decimal = 0;
    int length = strlen(binary);
    for(int i = 0; i < length; i++) {
        decimal = decimal * 2 + (binary[i] - '0');
    }
    return decimal;
}

int main() {
    char binary[100];
    printf("Enter a binary number: ");
    scanf("%s", binary);
    printf("Decimal: %d\n", binaryToInteger(binary));
    return 0;
}