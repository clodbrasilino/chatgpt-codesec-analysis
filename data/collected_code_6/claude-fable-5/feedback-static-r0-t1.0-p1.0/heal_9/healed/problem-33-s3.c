#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#define MAX_BITS (sizeof(unsigned int) * CHAR_BIT)
#define INPUT_SIZE 64

int decimal_to_binary(unsigned int decimal, char *buffer, size_t buffer_size)
{
    size_t index = 0;
    size_t i;

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
        buffer[0] = '\0';
        return -1;
    }

    buffer[index] = '\0';

    for (i = 0; i < index / 2; i++) {
        char temp = buffer[i];
        buffer[i] = buffer[index - 1 - i];
        buffer[index - 1 - i] = temp;
    }

    return 0;
}

static int read_unsigned(unsigned int *out)
{
    char input[INPUT_SIZE];
    char *endptr = NULL;
    unsigned long value;
    size_t len;

    if (out == NULL) {
        return -1;
    }

    memset(input, 0, sizeof(input));

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        return -1;
    }

    input[sizeof(input) - 1] = '\0';

    len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else if (len == sizeof(input) - 1) {
        int c;
        do {
            c = getchar();
        } while (c != '\n' && c != EOF);
        return -1;
    }

    if (input[0] == '\0') {
        return -1;
    }

    if (input[0] == '-') {
        return -1;
    }

    errno = 0;
    value = strtoul(input, &endptr, 10);

    if (errno == ERANGE || value > UINT_MAX) {
        return -1;
    }

    if (endptr == input) {
        return -1;
    }

    while (*endptr != '\0') {
        if (!isspace((unsigned char)*endptr)) {
            return -1;
        }
        endptr++;
    }

    *out = (unsigned int)value;
    return 0;
}

int main(void)
{
    unsigned int number = 0;
    char binary[MAX_BITS + 1];

    memset(binary, 0, sizeof(binary));

    printf("Enter a non-negative decimal number: ");
    fflush(stdout);

    if (read_unsigned(&number) != 0) {
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