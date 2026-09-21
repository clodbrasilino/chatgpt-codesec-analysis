#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t set_highest_unset_bit(uint32_t value)
{
    uint32_t bit = UINT32_C(1);

    while ((value & bit) != 0U && bit <= (UINT32_MAX >> 1)) {
        bit <<= 1;
    }

    return value | bit;
}

int main(void)
{
    char buffer[128];
    char *end;
    uintmax_t input;

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE || input > UINT32_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu32 "\n", set_highest_unset_bit((uint32_t)input));
    return EXIT_SUCCESS;
}