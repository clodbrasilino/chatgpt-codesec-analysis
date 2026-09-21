#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void decimalToBinary(int decimal, char *binary, size_t size) {
    size_t index = 0;

    if (decimal == 0) {
        if (size > 1) {
            binary[index++] = '0';
            binary[index] = '\0';
        }
        return;
    }

    while (decimal > 0 && index < size - 1) {
        binary[index++] = (decimal % 2) + '0';
        decimal /= 2;
    }
    binary[index] = '\0';

    for (size_t i = 0; i < index / 2; i++) {
        char temp = binary[i];
        binary[i] = binary[index - i - 1];
        binary[index - i - 1] = temp;
    }
}

int main(void) {
    int decimal;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary[sizeof(int) * CHAR_BIT + 1];

    printf("Enter a decimal number: ");
    if (scanf("%d", &decimal) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    decimalToBinary(decimal, binary, sizeof(binary));
    printf("Binary representation: %s\n", binary);

    return EXIT_SUCCESS;
}