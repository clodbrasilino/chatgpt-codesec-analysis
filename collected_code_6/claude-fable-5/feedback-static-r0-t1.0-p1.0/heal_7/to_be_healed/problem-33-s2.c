#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#define BINARY_BUFFER_SIZE (sizeof(unsigned int) * CHAR_BIT + 1U)
#define INPUT_BUFFER_SIZE 64U

static int decimal_to_binary(unsigned int decimal, char *buffer, size_t buffer_size)
{
    size_t index = 0;

    if (buffer == NULL || buffer_size < 2U) {
        return -1;
    }

    memset(buffer, 0, buffer_size);

    if (decimal == 0U) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return 0;
    }

    while (decimal > 0U) {
        if (index >= buffer_size - 1U) {
            return -1;
        }
        buffer[index] = (char)('0' + (decimal % 2U));
        index++;
        decimal /= 2U;
    }
    buffer[index] = '\0';

    for (size_t i = 0, j = index - 1U; i < j; i++, j--) {
        char temp = buffer[i];
        buffer[i] = buffer[j];
        buffer[j] = temp;
    }

    return 0;
}

static void discard_remaining_input(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != '\n' && ch != EOF);
}

static int read_unsigned(unsigned int *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_BUFFER_SIZE];
    char *endptr = NULL;
    unsigned long parsed;

    if (value == NULL) {
        return -1;
    }

    memset(input, 0, sizeof(input));

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        return -1;
    }

    input[sizeof(input) - 1U] = '\0';

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        discard_remaining_input();
        return -1;
    }

    if (strchr(input, '-') != NULL) {
        return -1;
    }

    errno = 0;
    parsed = strtoul(input, &endptr, 10);

    if (endptr == input) {
        return -1;
    }

    while (*endptr != '\0') {
        if (!isspace((unsigned char)*endptr)) {
            return -1;
        }
        endptr++;
    }

    if (errno == ERANGE || parsed > (unsigned long)UINT_MAX) {
        return -1;
    }

    *value = (unsigned int)parsed;
    return 0;
}

int main(void)
{
    unsigned int number = 0U;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary[BINARY_BUFFER_SIZE];

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

    printf("Binary representation: %s\n", binary);

    return EXIT_SUCCESS;
}