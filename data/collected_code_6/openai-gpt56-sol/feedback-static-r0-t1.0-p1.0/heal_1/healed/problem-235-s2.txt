#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t set_even_bits(uint32_t value)
{
    return value | UINT32_C(0x55555555);
}

int main(void)
{
    char input[64];
    char *end;
    uintmax_t parsed_value;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    errno = 0;
    end = input;
    parsed_value = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE || parsed_value > UINT32_MAX) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n' ||
           *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (printf("%" PRIu32 "\n", set_even_bits((uint32_t)parsed_value)) < 0) {
        return 1;
    }

    return 0;
}