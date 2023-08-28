#include <stdio.h>

void decimalToBinary(int decimal) {
    int binary[32];
    int i = 0;

    while(decimal > 0) {
        binary[i] = decimal % 2;
        decimal = decimal / 2;
        i++;
    }

    for(int j = i - 1; j >= 0; j--) {
        printf("%d", binary[j]);
    }
}

int main() {
    int decimal;
    printf("Enter a decimal number: ");
    scanf("%d", &decimal);
    printf("Binary equivalent: ");
    decimalToBinary(decimal);
    
    return 0;
}