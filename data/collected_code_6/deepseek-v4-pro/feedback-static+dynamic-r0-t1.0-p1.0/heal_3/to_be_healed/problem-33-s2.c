#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void decimalToBinary(int decimal, char *binary, size_t size) {
    size_t index = 0;

    if (size == 0) {
        return;
    }

    if (decimal == 0) {
        if (index + 1 < size) {
            binary[index++] = '0';
            binary[index] = '\0';
        }
        return;
    }

    int isNegative = 0;
    unsigned int num;

    if (decimal < 0) {
        isNegative = 1;
        num = (unsigned int)(-(unsigned int)decimal);
    } else {
        num = (unsigned int)decimal;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[65];
    size_t tempIndex = 0;
    size_t tempSize = sizeof(temp);

    while (num > 0) {
        if (tempIndex < tempSize - 1) {
            temp[tempIndex++] = (num % 2) + '0';
            num /= 2;
        } else {
            break;
        }
    }

    if (isNegative) {
        if (index < size) {
            binary[index++] = '-';
        }
    }

    while (tempIndex > 0 && index + 1 < size) {
        binary[index++] = temp[--tempIndex];
    }

    if (index < size) {
        binary[index] = '\0';
    } else {
        binary[size - 1] = '\0';
    }
}

int main(void) {
    int decimal;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary[65];

    printf("Enter a decimal number: ");
    if (scanf("%d", &decimal) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    decimalToBinary(decimal, binary, sizeof(binary));
    printf("Binary representation: %s\n", binary);

    return EXIT_SUCCESS;
}