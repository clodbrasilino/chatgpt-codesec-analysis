#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_BITS 64

int decimal_to_binary(unsigned long long decimal, char *buffer, size_t buffer_size)
{
    size_t index = 0;
    size_t i = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[MAX_BITS + 1];

    if (buffer == NULL || buffer_size == 0) {
        return -1;
    }

    memset(temp, 0, sizeof(temp));

    if (decimal == 0) {
        if (buffer_size < 2) {
            return -1;
        }
        buffer[0] = '0';
        buffer[1] = '\0';
        return 0;
    }

    while (decimal > 0 && index < MAX_BITS) {
        temp[index] = (char)('0' + (decimal % 2ULL));
        decimal /= 2ULL;
        index++;
    }

    if (decimal > 0) {
        return -1;
    }

    if (index >= buffer_size) {
        return -1;
    }

    for (i = 0; i < index; i++) {
        buffer[i] = temp[index - 1 - i];
    }
    buffer[index] = '\0';

    return 0;
}

int main(void)
{
    unsigned long long number = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary[MAX_BITS + 1];
    int scan_result = 0;

    memset(binary, 0, sizeof(binary));

    printf("Enter a non-negative decimal number: ");

    scan_result = scanf("%llu", &number);
    if (scan_result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (decimal_to_binary(number, binary, sizeof(binary)) != 0) {
        fprintf(stderr, "Error: conversion failed.\n");
        return EXIT_FAILURE;
    }

    printf("Binary equivalent: %s\n", binary);

    return EXIT_SUCCESS;
}