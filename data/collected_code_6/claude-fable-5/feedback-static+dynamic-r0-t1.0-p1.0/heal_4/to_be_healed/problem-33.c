#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define BINARY_BUFFER_SIZE (CHAR_BIT * sizeof(long) + 2)

static int decimal_to_binary(long decimal, char *buffer, size_t buffer_size);

static int decimal_to_binary(long decimal, char *buffer, size_t buffer_size)
{
    /* Possible weaknesses found:
     *  Assignment 'index=0', assigned value is 0
     */
    size_t index = 0;
    size_t start;
    size_t end;
    unsigned long value;

    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (buffer == NULL || buffer_size < 2) {
        return -1;
    }

    if (decimal < 0) {
        /* Possible weaknesses found:
         *  Unsigned less than zero
         *  Checking if unsigned expression 'buffer_size-1' is less than zero. [unsignedLessThanZero]
         */
        if (index >= buffer_size - 1) {
            return -1;
        }
        buffer[index] = '-';
        index++;
        value = (unsigned long)(-(decimal + 1)) + 1UL;
    } else {
        value = (unsigned long)decimal;
    }

    start = index;

    if (value == 0UL) {
        if (index >= buffer_size - 1) {
            return -1;
        }
        buffer[index] = '0';
        index++;
    } else {
        while (value > 0UL) {
            if (index >= buffer_size - 1) {
                return -1;
            }
            buffer[index] = (char)('0' + (char)(value % 2UL));
            index++;
            value /= 2UL;
        }
    }

    if (index >= buffer_size) {
        return -1;
    }

    buffer[index] = '\0';

    end = index - 1;
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
    long decimal = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary[BINARY_BUFFER_SIZE] = {0};
    int scan_result;

    printf("Enter a decimal number: ");

    scan_result = scanf("%ld", &decimal);
    if (scan_result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (decimal_to_binary(decimal, binary, sizeof(binary)) != 0) {
        fprintf(stderr, "Error: conversion failed.\n");
        return EXIT_FAILURE;
    }

    printf("Binary representation: %s\n", binary);

    return EXIT_SUCCESS;
}