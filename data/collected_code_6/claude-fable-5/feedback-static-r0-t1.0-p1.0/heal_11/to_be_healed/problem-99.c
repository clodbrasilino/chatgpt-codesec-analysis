#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>

#define MAX_BITS (sizeof(unsigned int) * CHAR_BIT)
#define INPUT_SIZE 64U

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
        buffer[0] = '\0';
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

static int read_unsigned(unsigned int *out)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE];
    char *endptr = NULL;
    unsigned long parsed;
    size_t len;

    if (out == NULL) {
        return -1;
    }

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    if (len > 0U && input[len - 1U] == '\n') {
        input[len - 1U] = '\0';
    } else {
        int ch;
        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while (ch != '\n' && ch != EOF);
    }

    if (input[0] == '\0') {
        return -1;
    }

    if (!isdigit((unsigned char)input[0])) {
        return -1;
    }

    errno = 0;
    parsed = strtoul(input, &endptr, 10);
    if (errno != 0 || endptr == input || parsed > UINT_MAX) {
        return -1;
    }

    while (*endptr != '\0') {
        if (!isspace((unsigned char)*endptr)) {
            return -1;
        }
        endptr++;
    }

    *out = (unsigned int)parsed;
    return 0;
}

int main(void)
{
    unsigned int value = 0U;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary[MAX_BITS + 1U] = {0};

    printf("Enter a non-negative decimal number: ");
    fflush(stdout);

    if (read_unsigned(&value) != 0) {
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