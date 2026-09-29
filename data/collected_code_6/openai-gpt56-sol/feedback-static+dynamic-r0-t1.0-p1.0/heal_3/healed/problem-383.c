#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t toggle_odd_bits(uint32_t value)
{
    return value ^ UINT32_C(0xAAAAAAAA);
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end = NULL;
    uintmax_t value;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == 0 || input[length - 1] != '\n') {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(input, &end, 0);

    if (errno == ERANGE || end == input || value > UINT32_MAX) {
        free(input);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu32 "\n", toggle_odd_bits((uint32_t)value)) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}