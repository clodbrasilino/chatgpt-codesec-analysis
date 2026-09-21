#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>

#define MAX_BITS 64
#define INPUT_SIZE 128

static int decimal_to_binary(unsigned long long value, char *buffer, size_t buffer_size)
{
    size_t index = 0;
    size_t i;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[MAX_BITS + 1];

    if (buffer == NULL || buffer_size < 2) {
        return -1;
    }

    memset(temp, 0, sizeof(temp));

    if (value == 0ULL) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return 0;
    }

    while (value > 0ULL) {
        if (index >= MAX_BITS) {
            return -1;
        }
        temp[index] = (char)('0' + (value & 1ULL));
        value >>= 1ULL;
        index++;
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

static int read_long_long(long long *out)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char line[INPUT_SIZE];
    char *endptr = NULL;
    long long value;

    if (out == NULL) {
        return -1;
    }

    memset(line, 0, sizeof(line));

    if (fgets(line, (int)sizeof(line), stdin) == NULL) {
        return -1;
    }

    line[sizeof(line) - 1] = '\0';

    if (strchr(line, '\n') == NULL && !feof(stdin)) {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        return -1;
    }

    errno = 0;
    value = strtoll(line, &endptr, 10);

    if (endptr == line) {
        return -1;
    }

    if (errno == ERANGE) {
        return -1;
    }

    while (*endptr != '\0') {
        if (!isspace((unsigned char)*endptr)) {
            return -1;
        }
        endptr++;
    }

    *out = value;
    return 0;
}

int main(void)
{
    long long input = 0;
    unsigned long long magnitude;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary[MAX_BITS + 1];
    int is_negative = 0;

    memset(binary, 0, sizeof(binary));

    printf("Enter a decimal number: ");
    fflush(stdout);

    if (read_long_long(&input) != 0) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (input < 0) {
        is_negative = 1;
        if (input == LLONG_MIN) {
            magnitude = (unsigned long long)LLONG_MAX + 1ULL;
        } else {
            magnitude = (unsigned long long)(-input);
        }
    } else {
        magnitude = (unsigned long long)input;
    }

    if (decimal_to_binary(magnitude, binary, sizeof(binary)) != 0) {
        fprintf(stderr, "Error: conversion failed.\n");
        return EXIT_FAILURE;
    }

    if (is_negative) {
        printf("Binary equivalent: -%s\n", binary);
    } else {
        printf("Binary equivalent: %s\n", binary);
    }

    return EXIT_SUCCESS;
}