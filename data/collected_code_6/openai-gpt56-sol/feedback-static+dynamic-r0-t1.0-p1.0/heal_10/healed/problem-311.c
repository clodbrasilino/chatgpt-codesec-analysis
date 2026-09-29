#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t set_rightmost_unset_bit(uint32_t value)
{
    uint32_t bit;

    for (bit = UINT32_C(1); bit != 0; bit <<= 1) {
        if ((value & bit) == 0) {
            return value | bit;
        }
    }

    return value;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    char *end = NULL;
    uintmax_t parsed;

    if (getline(&line, &capacity, stdin) == -1) {
        free(line);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(line, &end, 0);

    if (line == end || errno == ERANGE || parsed > UINT32_MAX) {
        free(line);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return EXIT_FAILURE;
    }

    printf("%" PRIu32 "\n",
           set_rightmost_unset_bit((uint32_t)parsed));

    free(line);
    return EXIT_SUCCESS;
}