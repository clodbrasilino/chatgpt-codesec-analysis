#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *decimal_to_binary(uint64_t value)
{
    enum { BINARY_BUFFER_SIZE = 65 };
    char buffer[BINARY_BUFFER_SIZE];
    size_t index = BINARY_BUFFER_SIZE - 1;
    size_t length;
    char *result;

    buffer[index] = '\0';

    do {
        buffer[--index] = (char)('0' + (value & UINT64_C(1)));
        value >>= 1;
    } while (value != 0);

    length = BINARY_BUFFER_SIZE - index;
    result = malloc(length);

    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < length; ++i) {
        result[i] = buffer[index + i];
    }

    return result;
}

int main(void)
{
    char input[128];
    char *end;
    uintmax_t parsed;
    uint64_t decimal;
    char *binary;

    fputs("Enter a non-negative decimal number: ", stdout);
    fflush(stdout);

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (input[0] == '-') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    parsed = strtoumax(input, &end, 10);

    if (end == input || parsed > UINT64_MAX) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    decimal = (uint64_t)parsed;
    binary = decimal_to_binary(decimal);

    if (binary == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Binary: %s\n", binary);
    free(binary);

    return EXIT_SUCCESS;
}