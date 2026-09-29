#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t toggle_even_bits(uint32_t value)
{
    return value ^ UINT32_C(0x55555555);
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length = getline(&input, &capacity, stdin);

    if (length < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';
    } else if (!feof(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE || parsed > UINT32_MAX) {
        free(input);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    uint32_t result = toggle_even_bits((uint32_t)parsed);
    free(input);

    if (printf("%" PRIu32 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}