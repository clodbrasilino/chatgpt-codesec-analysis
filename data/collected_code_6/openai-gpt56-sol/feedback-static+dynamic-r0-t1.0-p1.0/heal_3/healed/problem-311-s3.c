#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t set_leftmost_unset_bit(uint32_t value)
{
    uint32_t mask = UINT32_C(1);

    while ((value & mask) != 0U && mask != 0U) {
        mask <<= 1U;
    }

    return mask == 0U ? value : value | mask;
}

int main(void)
{
    char line[64];
    char *end;
    uintmax_t input;

    if (fgets(line, sizeof line, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(line, &end, 10);

    if (end == line || errno == ERANGE || input > UINT32_MAX) {
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

    printf("%" PRIu32 "\n", set_leftmost_unset_bit((uint32_t)input));
    return EXIT_SUCCESS;
}