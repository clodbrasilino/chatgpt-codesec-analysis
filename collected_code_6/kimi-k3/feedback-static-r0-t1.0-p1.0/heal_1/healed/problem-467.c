#include <stdio.h>
#include <stdlib.h>

void decimalToOctal(int decimalNumber) {
    int octalNumber[32];
    int i = 0;
    
    if (decimalNumber == 0) {
        printf("0");
        return;
    }
    
    if (decimalNumber < 0) {
        printf("-");
        decimalNumber = -decimalNumber;
    }
    
    while (decimalNumber > 0) {
        octalNumber[i] = decimalNumber % 8;
        decimalNumber = decimalNumber / 8;
        i++;
    }
    
    for (int j = i - 1; j >= 0; j--) {
        printf("%d", octalNumber[j]);
    }
}

int main(void) {
    int decimalNumber;
    
    printf("Enter a decimal number: ");
    
    if (scanf("%d", &decimalNumber) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Octal equivalent: ");
    decimalToOctal(decimalNumber);
    printf("\n");
    
    return EXIT_SUCCESS;
}