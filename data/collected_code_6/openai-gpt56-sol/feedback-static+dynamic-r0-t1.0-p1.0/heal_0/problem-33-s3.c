#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *decimal_to_binary(uint64_t value)
{
    char buffer[65];
    size_t index = sizeof(buffer) - 1;
    size_t length;
    char *result;

    buffer[index] = '\0';

    do {
        buffer[--index] = (char)('0' + (value & UINT64_C(1)));
        value >>= 1;
    } while (value != 0);

    length = sizeof(buffer) - index;
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
    uint64_t decimal;
    char *binary;

    printf("Enter a non-negative decimal number: ");

    if (scanf("%" SCNu64, &decimal) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    binary = decimal_to_binary(decimal);

    if (binary == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    printf("Binary: %s\n", binary);
    free(binary);

    return EXIT_SUCCESS;
}