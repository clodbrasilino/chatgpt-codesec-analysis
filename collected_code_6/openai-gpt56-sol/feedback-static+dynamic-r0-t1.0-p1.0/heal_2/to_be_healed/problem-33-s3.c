#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *decimal_to_binary(uint64_t value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[65];
    size_t index = sizeof buffer - 1;

    buffer[index] = '\0';

    do {
        buffer[--index] = (char)('0' + (value & UINT64_C(1)));
        value >>= 1;
    } while (value != 0);

    size_t length = sizeof buffer - index;
    char *result = malloc(length);

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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end;
    uintmax_t parsed_value;
    char *binary;

    printf("Enter a non-negative decimal number: ");

    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    end = input;
    parsed_value = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE || parsed_value > UINT64_MAX) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n') {
        ++end;
    }

    if (*end != '\0' || input[0] == '-') {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    binary = decimal_to_binary((uint64_t)parsed_value);

    if (binary == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    printf("Binary: %s\n", binary);
    free(binary);

    return EXIT_SUCCESS;
}