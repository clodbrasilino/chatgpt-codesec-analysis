#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *decimal_to_binary(uint64_t value)
{
    size_t bits = 1;
    uint64_t temp = value;

    while (temp > 1) {
        temp >>= 1;
        ++bits;
    }

    char *result = malloc(bits + 1);
    if (result == NULL) {
        return NULL;
    }

    result[bits] = '\0';

    for (size_t i = bits; i > 0; --i) {
        result[i - 1] = (char)('0' + (value & UINT64_C(1)));
        value >>= 1;
    }

    return result;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    uintmax_t parsed;
    char *binary;

    fputs("Enter a non-negative decimal number: ", stdout);
    fflush(stdout);

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE || parsed > UINT64_MAX) {
        free(input);
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    binary = decimal_to_binary((uint64_t)parsed);
    free(input);

    if (binary == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Binary: %s\n", binary);
    free(binary);

    return EXIT_SUCCESS;
}