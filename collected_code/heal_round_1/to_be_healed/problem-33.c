#include <stdio.h>

void decimalToBinary(int decimalNumber) {
    int binaryNumber[32];
    int i = 0;

    while (decimalNumber > 0) {
        binaryNumber[i] = decimalNumber % 2;
        decimalNumber /= 2;
        i++;
    }

    for (int j = i - 1; j >= 0; j--) {
        /* Possible weaknesses found:
         *  Cannot determine that 'binaryNumber[j]' is initialized [premium-bughuntingUninit]
         */
        printf("%d", binaryNumber[j]);
    }
}

int main() {
    int decimalNumber;
    printf("Enter a decimal number: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'decimalNumber' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &decimalNumber);

    printf("Binary representation: ");
    decimalToBinary(decimalNumber);

    return 0;
}