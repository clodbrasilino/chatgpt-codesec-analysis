#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define BINARY_BUFFER_SIZE (sizeof(unsigned int) * CHAR_BIT + 1)

static int decimal_to_binary(unsigned int decimal, char *buffer, size_t buffer_size)
{
    size_t index = 0;

    if (buffer == NULL || buffer_size < 2) {
        return -1;
    }

    if (decimal == 0) {
        buffer[index++] = '0';
        buffer[index] = '\0';
        return 0;
    }

    while (decimal > 0) {
        if (index >= buffer_size - 1) {
            buffer[0] = '\0';
            return -1;
        }
        buffer[index++] = (char)('0' + (decimal % 2U));
        decimal /= 2U;
    }
    buffer[index] = '\0';

    for (size_t i = 0, j = index - 1; i < j; i++, j--) {
        char temp = buffer[i];
        buffer[i] = buffer[j];
        buffer[j] = temp;
    }

    return 0;
}

int main(void)
{
    unsigned int number = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary[BINARY_BUFFER_SIZE];
    int result;

    printf("Enter a non-negative decimal number: ");

    result = scanf("%u", &number);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (decimal_to_binary(number, binary, sizeof(binary)) != 0) {
        fprintf(stderr, "Error: conversion failed.\n");
        return EXIT_FAILURE;
    }

    printf("Binary representation: %s\n", binary);

    return EXIT_SUCCESS;
}