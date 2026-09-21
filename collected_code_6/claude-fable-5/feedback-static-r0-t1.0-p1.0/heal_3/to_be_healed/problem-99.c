#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_BITS (sizeof(unsigned int) * CHAR_BIT)

static int decimal_to_binary(unsigned int number, char *buffer, size_t buffer_size)
{
    size_t index = 0U;
    size_t start;
    size_t end;

    if (buffer == NULL || buffer_size < 2U) {
        return -1;
    }

    if (number == 0U) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return 0;
    }

    while (number > 0U && index < (buffer_size - 1U)) {
        buffer[index] = (char)('0' + (number % 2U));
        number /= 2U;
        index++;
    }

    if (number > 0U) {
        return -1;
    }

    buffer[index] = '\0';

    start = 0U;
    end = index - 1U;
    while (start < end) {
        char temp = buffer[start];
        buffer[start] = buffer[end];
        buffer[end] = temp;
        start++;
        end--;
    }

    return 0;
}

int main(void)
{
    unsigned int value = 0U;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary[MAX_BITS + 1U];
    int scan_result;

    printf("Enter a non-negative decimal number: ");

    scan_result = scanf("%u", &value);
    if (scan_result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (decimal_to_binary(value, binary, sizeof(binary)) != 0) {
        fprintf(stderr, "Error: conversion failed.\n");
        return EXIT_FAILURE;
    }

    printf("Binary equivalent: %s\n", binary);

    return EXIT_SUCCESS;
}