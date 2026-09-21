#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <errno.h>

#define TEMP_SIZE ((sizeof(unsigned long) * CHAR_BIT + 2) / 3 + 1)
#define OCTAL_BUFFER_SIZE (TEMP_SIZE + 2)
#define INPUT_BUFFER_SIZE 64

int decimal_to_octal(long decimal, char *buffer, size_t buffer_size)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[TEMP_SIZE];
    size_t index = 0;
    size_t i;
    int negative = 0;
    unsigned long value;

    if (buffer == NULL || buffer_size < 2) {
        return -1;
    }

    memset(temp, 0, sizeof(temp));

    if (decimal < 0) {
        negative = 1;
        value = (unsigned long)(-(decimal + 1)) + 1UL;
    } else {
        value = (unsigned long)decimal;
    }

    if (value == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return 0;
    }

    while (value > 0 && index < sizeof(temp)) {
        temp[index] = (char)('0' + (value % 8UL));
        value /= 8UL;
        index++;
    }

    if (value > 0) {
        return -1;
    }

    if (index + (size_t)negative + 1 > buffer_size) {
        return -1;
    }

    i = 0;
    if (negative == 1) {
        buffer[i] = '-';
        i++;
    }

    while (index > 0 && i < buffer_size - 1) {
        index--;
        buffer[i] = temp[index];
        i++;
    }
    buffer[i] = '\0';

    return 0;
}

int main(void)
{
    long decimal;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char octal[OCTAL_BUFFER_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_BUFFER_SIZE];
    char *endptr;

    memset(octal, 0, sizeof(octal));
    memset(input, 0, sizeof(input));

    printf("Enter a decimal number: ");

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\n")] = '\0';

    if (input[0] == '\0') {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    decimal = strtol(input, &endptr, 10);

    if (errno == ERANGE || endptr == input || *endptr != '\0') {
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