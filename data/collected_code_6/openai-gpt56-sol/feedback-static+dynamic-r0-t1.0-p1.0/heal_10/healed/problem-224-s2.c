#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int count_set_bits(uint64_t value)
{
    unsigned int count = 0;

    while (value != UINT64_C(0)) {
        value &= value - UINT64_C(1);
        ++count;
    }

    return count;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length = getline(&line, &capacity, stdin);

    if (length < 0) {
        free(line);
        return EXIT_FAILURE;
    }

    if (length > 0 && line[length - 1] == '\n') {
        line[--length] = '\0';
    } else if (!feof(stdin)) {
        free(line);
        return EXIT_FAILURE;
    }

    if (length > 0 && line[length - 1] == '\r') {
        line[--length] = '\0';
    }

    char *start = line;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        free(line);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t value = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || value > UINT64_MAX) {
        free(line);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return EXIT_FAILURE;
    }

    unsigned int result = count_set_bits((uint64_t)value);
    free(line);

    if (printf("%u\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}