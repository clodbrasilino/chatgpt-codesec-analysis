#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static uint32_t toggle_even_bits(uint32_t value)
{
    return value ^ UINT32_C(0x55555555);
}

int main(void)
{
    char input[64];
    char *end = NULL;
    uintmax_t parsed;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    errno = 0;
    parsed = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || parsed > UINT32_MAX) {
        return 1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        return 1;
    }

    printf("%" PRIu32 "\n", toggle_even_bits((uint32_t)parsed));

    return 0;
}