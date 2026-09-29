#include <stdio.h>
#include <math.h>
#include <string.h>

int octalToDecimal(char* octal) {
    int decimal = 0;
    int length = strlen(octal);
    for(int i = 0; i < length; i++) {
        if(octal[i] < '0' || octal[i] > '7'){
            printf("Invalid octal number\n");
            return -1;
        }
        decimal += (octal[i] - '0') * pow(8, length - i - 1);
    }
    return decimal;
}

int main() {
    char octal[50];
    printf("Enter an octal number: ");
    scanf("%49s", octal);
    int decimal = octalToDecimal(octal);
    if(decimal >= 0) {
        printf("Decimal: %d\n", decimal);
    } 
    return 0;
}