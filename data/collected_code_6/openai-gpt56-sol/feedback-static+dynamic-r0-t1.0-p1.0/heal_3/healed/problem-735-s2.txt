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
    char *line = NULL;
    size_t capacity = 0;
    char *end;
    uintmax_t value;

    if (getline(&line, &capacity, stdin) < 0) {
        free(line);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(line, &end, 10);

    if (end == line || errno == ERANGE || value > UINT32_MAX) {
        free(line);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu32 "\n", toggle_inner_bits((uint32_t)value));
    free(line);
    return EXIT_SUCCESS;
}