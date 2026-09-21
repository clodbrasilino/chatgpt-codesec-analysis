#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

#define MAX_BITS (sizeof(unsigned int) * CHAR_BIT)
#define LINE_SIZE 64

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

static int discard_remaining_input(void)
{
    int ch;
    size_t guard = 0;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        guard++;
        if (guard > (size_t)INT_MAX) {
            return -1;
        }
    }

    if (ch == EOF && ferror(stdin)) {
        return -1;
    }

    return 0;
}

int main(void)
{
    unsigned int number = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary[MAX_BITS + 1] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char line[LINE_SIZE] = {0};
    char *endptr = NULL;
    unsigned long parsed;
    size_t len;

    printf("Enter a non-negative decimal number: ");
    if (fflush(stdout) != 0) {
        fprintf(stderr, "Error: output stream error.\n");
        return EXIT_FAILURE;
    }

    if (fgets(line, sizeof(line), stdin) == NULL) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    line[sizeof(line) - 1] = '\0';
    len = strnlen(line, sizeof(line));

    if (len == sizeof(line) - 1 && line[len - 1] != '\n') {
        if (discard_remaining_input() != 0) {
            fprintf(stderr, "Error: input stream error.\n");
            return EXIT_FAILURE;
        }
        fprintf(stderr, "Error: input too long.\n");
        return EXIT_FAILURE;
    }

    if (len > 0 && line[len - 1] == '\n') {
        line[len - 1] = '\0';
        len--;
    }

    if (len == 0 || line[0] == '\0') {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (line[0] == '-') {
        fprintf(stderr, "Error: number must be non-negative.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoul(line, &endptr, 10);

    if (endptr == line || endptr == NULL || *endptr != '\0') {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (errno == ERANGE || parsed > UINT_MAX) {
        fprintf(stderr, "Error: number out of range.\n");
        return EXIT_FAILURE;
    }

    number = (unsigned int)parsed;

    if (decimal_to_binary(number, binary, sizeof(binary)) != 0) {
        fprintf(stderr, "Error: conversion failed.\n");
        return EXIT_FAILURE;
    }

    printf("Decimal: %u\n", number);
    printf("Binary: %s\n", binary);

    return EXIT_SUCCESS;
}