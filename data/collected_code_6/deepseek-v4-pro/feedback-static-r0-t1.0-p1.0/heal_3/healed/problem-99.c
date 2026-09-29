#include <stdio.h>
#include <stdlib.h>

void decimalToBinary(int n) {
    char binary[33];
    int index = 0;

    if (n == 0) {
        printf("0");
        return;
    }

    while (n > 0) {
        binary[index] = (n % 2) + '0';
        n = n / 2;
        index++;
    }
    binary[index] = '\0';

    for (int i = index - 1; i >= 0; i--) {
        printf("%c", binary[i]);
    }
}

int main(void) {
    int num;

    printf("Enter a decimal number: ");
    if (scanf("%d", &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (num < 0) {
        fprintf(stderr, "Please enter a non-negative integer\n");
        return 1;
    }

    printf("Binary equivalent: ");
    decimalToBinary(num);
    printf("\n");

    return 0;
}