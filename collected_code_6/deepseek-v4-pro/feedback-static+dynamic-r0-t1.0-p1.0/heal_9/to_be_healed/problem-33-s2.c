#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void decimalToBinary(int decimal, char *binary, size_t size) {
    if (size == 0) {
        return;
    }

    if (decimal == 0) {
        if (size >= 2) {
            binary[0] = '0';
            binary[1] = '\0';
        } else {
            binary[0] = '\0';
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

    while (num > 0 && tempIndex < tempSize - 1) {
        temp[tempIndex++] = (num % 2) + '0';
        num /= 2;
    }
    temp[tempIndex] = '\0';

    size_t index = 0;

    if (isNegative && index < size - 1) {
        binary[index++] = '-';
    }

    while (tempIndex > 0 && index < size - 1) {
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
    int result;

    printf("Enter a decimal number: ");
    result = scanf("%d", &decimal);

    if (result != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (decimal == INT_MIN) {
        unsigned int absValue = (unsigned int)INT_MAX + 1;
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char tempBinary[65];
        decimalToBinary((int)absValue, tempBinary, sizeof(tempBinary));
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char negBinary[67];
        int written = snprintf(negBinary, sizeof(negBinary), "-%s", tempBinary);
        if (written < 0 || (size_t)written >= sizeof(negBinary)) {
            fprintf(stderr, "Output truncation occurred\n");
            return EXIT_FAILURE;
        }
        printf("Binary representation: %s\n", negBinary);
    } else {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char binary[65];
        decimalToBinary(decimal, binary, sizeof(binary));
        printf("Binary representation: %s\n", binary);
    }

    return EXIT_SUCCESS;
}