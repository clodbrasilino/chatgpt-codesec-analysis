#include<stdio.h>
#include<string.h>

int binaryToDecimal(char *binary) {
    int length = strlen(binary);
    int decimal = 0;
    int base = 1;

    for(int i = length-1; i >= 0; i--) {
        if(binary[i] == '1') {
            decimal += base;
        }
        base = base * 2;
    }

    return decimal;
}

int main() {
    char binary[100];
    printf("Enter a binary number: ");
    scanf("%s", binary);

    for(int i = 0; binary[i] != '\0'; i++) {
        if(binary[i] != '0' && binary[i] != '1') { 
            printf("Error! Invalid binary number.\n");
            return 0;
        }
    }

    printf("Decimal equivalent is: %d\n", binaryToDecimal(binary));

    return 0;
}