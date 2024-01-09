#include <stdio.h>

int isHexEvenOrOdd(char hex[]) {
    int i = 0;
    
    // Skip any leading "0x" or "0X"
    if (hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X'))
        i = 2;
    
    // Iterate through each digit of the hexadecimal number
    while (hex[i] != '\0') {
        // If the current digit is not a valid hexadecimal digit, return 0
        if (!((hex[i] >= '0' && hex[i] <= '9') || (hex[i] >= 'A' && hex[i] <= 'F') || (hex[i] >= 'a' && hex[i] <= 'f')))
            return 0;
        
        i++;
    }
    
    // Determine the numerical value of the hexadecimal number
    int decimal = 0;
    i = 0;
    while (hex[i] != '\0') {
        if (hex[i] >= '0' && hex[i] <= '9')
            decimal = decimal * 16 + (hex[i] - '0');
        else if (hex[i] >= 'A' && hex[i] <= 'F')
            decimal = decimal * 16 + (hex[i] - 'A' + 10);
        else if (hex[i] >= 'a' && hex[i] <= 'f')
            decimal = decimal * 16 + (hex[i] - 'a' + 10);
        
        i++;
    }
    
    // Check if the decimal value is even or odd
    if (decimal % 2 == 0)
        return 1; // Even
    else
        return 0; // Odd
}

int main() {
    char hex[20];
    printf("Enter a hexadecimal number: ");
    scanf("%s", hex);
    
    if (isHexEvenOrOdd(hex))
        printf("The hexadecimal number is even.\n");
    else
        printf("The hexadecimal number is odd.\n");
    
    return 0;
}