#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t set_odd_bits(uint64_t value)
{
    return value | UINT64_C(0xAAAAAAAAAAAAAAAA);
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    uintmax_t value;

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return EXIT_FAILURE;
    }

    if (length == 0 || line[length - 1] != '\n') {
        free(line);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(line, &end, 0);

    if (end == line || errno == ERANGE) {
        free(line);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end == '\n') {
        ++end;
    }

    if (*end != '\0' || value > UINT64_MAX) {
        free(line);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", set_odd_bits((uint64_t)value)) < 0) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}