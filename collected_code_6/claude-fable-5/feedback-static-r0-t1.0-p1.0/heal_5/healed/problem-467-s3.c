#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define OCTAL_TEMP_SIZE (((sizeof(unsigned long) * CHAR_BIT + 2) / 3) + 1)
#define OCTAL_BUFFER_SIZE (((sizeof(unsigned long) * CHAR_BIT + 2) / 3) + 3)

int decimal_to_octal(long decimal, char *buffer, size_t buffer_size);

int decimal_to_octal(long decimal, char *buffer, size_t buffer_size)
{
    char temp[OCTAL_TEMP_SIZE];
    size_t index = 0;
    size_t i;
    int negative = 0;
    unsigned long value;

    if (buffer == NULL || buffer_size < 2) {
        return -1;
    }

    if (decimal < 0) {
        negative = 1;
        value = (unsigned long)(-(decimal + 1)) + 1UL;
    } else {
        value = (unsigned long)decimal;
    }

    if (value == 0UL) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return 0;
    }

    while (value > 0UL) {
        if (index >= sizeof(temp)) {
            return -1;
        }
        temp[index] = (char)('0' + (value % 8UL));
        value /= 8UL;
        index++;
    }

    if (index + (size_t)negative + 1 > buffer_size) {
        return -1;
    }

    i = 0;
    if (negative == 1) {
        buffer[i] = '-';
        i++;
    }

    while (index > 0) {
        index--;
        if (i >= buffer_size - 1) {
            return -1;
        }
        buffer[i] = temp[index];
        i++;
    }
    buffer[i] = '\0';

    return 0;
}

int main(void)
{
    long decimal;
    char octal[OCTAL_BUFFER_SIZE];
    int scan_result;

    printf("Enter a decimal number: ");
    scan_result = scanf("%ld", &decimal);

    if (scan_result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (decimal_to_octal(decimal, octal, sizeof(octal)) != 0) {
        fprintf(stderr, "Error: conversion failed.\n");
        return EXIT_FAILURE;
    }

    printf("Octal representation: %s\n", octal);

    return EXIT_SUCCESS;
}