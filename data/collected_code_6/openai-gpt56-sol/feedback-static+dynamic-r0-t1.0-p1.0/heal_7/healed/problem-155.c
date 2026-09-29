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
    ssize_t length;
    char *end;
    uintmax_t parsed;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        return 1;
    }

    errno = 0;
    parsed = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || parsed > UINT32_MAX) {
        free(input);
        return 1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return 1;
    }

    if (printf("%" PRIu32 "\n",
               toggle_even_bits((uint32_t)parsed)) < 0) {
        free(input);
        return 1;
    }

    free(input);
    return 0;
}