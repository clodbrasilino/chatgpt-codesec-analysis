#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void decimalToBinary(unsigned int n) {
    char binary[sizeof(unsigned int) * CHAR_BIT + 1];
    int index = 0;

    if (n == 0) {
        printf("0");
        return;
    }

    while (n > 0 && index < (int)(sizeof(binary) - 1)) {
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
    long long input;
    char extra;

    printf("Enter a decimal number: ");
    if (scanf("%lld%c", &input, &extra) != 2 || extra != '\n') {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (input < 0 || input > UINT_MAX) {
        fprintf(stderr, "Please enter a non-negative integer within valid range\n");
        return 1;
    }

    printf("Binary equivalent: ");
    decimalToBinary((unsigned int)input);
    printf("\n");

    return 0;
}