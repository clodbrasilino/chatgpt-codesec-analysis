#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t toggle_inner_bits(uint32_t number)
{
    const uint32_t inner_mask = (UINT32_MAX >> 1U) & ~UINT32_C(1);
    return number ^ inner_mask;
}

int main(void)
{
    char input[128];
    char *end;
    uintmax_t value;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = input;
    value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || value > UINT32_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu32 "\n", toggle_inner_bits((uint32_t)value));
    return EXIT_SUCCESS;
}