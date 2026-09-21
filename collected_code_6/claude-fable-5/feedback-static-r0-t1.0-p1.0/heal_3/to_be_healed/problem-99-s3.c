#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX_BITS 64

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
    memset(buffer, 0, buffer_size);

    if (value == 0ULL) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return 0;
    }

    while (value > 0ULL && index < MAX_BITS) {
        temp[index] = (char)('0' + (value & 1ULL));
        value >>= 1ULL;
        index++;
    }

    if (value > 0ULL) {
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
    long long input = 0;
    unsigned long long magnitude = 0ULL;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary[MAX_BITS + 1];
    int is_negative = 0;

    memset(binary, 0, sizeof(binary));

    printf("Enter a decimal number: ");

    if (scanf("%lld", &input) != 1) {
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