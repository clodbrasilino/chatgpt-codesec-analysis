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
    char *line = NULL;
    size_t capacity = 0;
    char *end;
    uintmax_t parsed;
    int trailing;

    if (getline(&line, &capacity, stdin) < 0) {
        free(line);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(line, &end, 10);

    if (end == line || errno == ERANGE || parsed > UINT32_MAX ||
        sscanf(end, " %c", (char *)&trailing) == 1) {
        free(line);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(line);
    printf("%" PRIu32 "\n", toggle_odd_bits((uint32_t)parsed));
    return EXIT_SUCCESS;
}