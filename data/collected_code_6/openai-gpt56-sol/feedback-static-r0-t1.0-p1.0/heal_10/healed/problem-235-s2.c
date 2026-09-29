#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t set_even_bits(uint32_t value)
{
    return value | UINT32_C(0x55555555);
}

static int read_line(char **buffer)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t length;

    if (buffer == NULL) {
        return 0;
    }

    *buffer = NULL;

    errno = 0;
    length = getline(&line, &capacity, stdin);

    if (length == (size_t)-1) {
        free(line);
        return 0;
    }

    if (length > 0 && line[length - 1] == '\n') {
        line[--length] = '\0';
    }

    if (length > 0 && line[length - 1] == '\r') {
        line[length - 1] = '\0';
    }

    *buffer = line;
    return 1;
}

int main(void)
{
    char *input = NULL;
    char *end = NULL;
    uintmax_t parsed_value;
    uint32_t result;

    if (!read_line(&input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_value = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE || parsed_value > UINT32_MAX) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    result = set_even_bits((uint32_t)parsed_value);
    free(input);

    if (printf("%" PRIu32 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}