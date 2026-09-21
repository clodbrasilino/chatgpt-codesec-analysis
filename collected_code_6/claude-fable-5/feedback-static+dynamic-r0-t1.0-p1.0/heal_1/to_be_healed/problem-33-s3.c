#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_BITS (sizeof(unsigned int) * CHAR_BIT)

int decimal_to_binary(unsigned int decimal, char *buffer, size_t buffer_size)
{
    size_t index = 0;
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    char temp;

    if (buffer == NULL || buffer_size < 2) {
        return -1;
    }

    if (decimal == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return 0;
    }

    while (decimal > 0 && index < buffer_size - 1) {
        buffer[index] = (char)('0' + (decimal % 2U));
        decimal /= 2U;
        index++;
    }

    if (decimal > 0) {
        return -1;
    }

    buffer[index] = '\0';

    for (i = 0; i < index / 2; i++) {
        temp = buffer[i];
        buffer[i] = buffer[index - 1 - i];
        buffer[index - 1 - i] = temp;
    }

    return 0;
}

int main(void)
{
    unsigned int number = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary[MAX_BITS + 1];
    int scan_result;

    printf("Enter a non-negative decimal number: ");

    scan_result = scanf("%u", &number);
    if (scan_result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (decimal_to_binary(number, binary, sizeof(binary)) != 0) {
        fprintf(stderr, "Error: conversion failed.\n");
        return EXIT_FAILURE;
    }

    printf("Decimal: %u\n", number);
    printf("Binary: %s\n", binary);

    return EXIT_SUCCESS;
}