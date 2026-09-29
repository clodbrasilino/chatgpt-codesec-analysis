#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void decimal_to_octal(int decimal, char *octal, size_t size) {
    int index = 0;
    
    if (decimal == 0) {
        if (size < 2) {
            octal[0] = '\0';
            return;
        }
        octal[index++] = '0';
        octal[index] = '\0';
        return;
    }
    
    while (decimal > 0 && index < size - 1) {
        octal[index++] = (decimal % 8) + '0';
        decimal /= 8;
    }
    octal[index] = '\0';
    
    for (int i = 0; i < index / 2; i++) {
        char temp = octal[i];
        octal[i] = octal[index - 1 - i];
        octal[index - 1 - i] = temp;
    }
}

int main(void) {
    int decimal;
    char octal[64];
    
    printf("Enter a decimal number: ");
    if (scanf("%d", &decimal) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (decimal < 0) {
        fprintf(stderr, "Negative numbers not supported\n");
        return EXIT_FAILURE;
    }
    
    decimal_to_octal(decimal, octal, sizeof(octal));
    printf("Octal: %s\n", octal);
    
    return EXIT_SUCCESS;
}