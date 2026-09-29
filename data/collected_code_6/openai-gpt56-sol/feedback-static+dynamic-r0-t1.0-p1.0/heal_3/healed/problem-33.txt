#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

static int decimal_to_binary(unsigned long long value, char *buffer, size_t size)
{
    const size_t required = sizeof value * CHAR_BIT + 1;
    size_t position = required - 1;

    if (buffer == NULL || size < required) {
        return 0;
    }

    buffer[position] = '\0';

    do {
        buffer[--position] = (char)('0' + (value & 1ULL));
        value >>= 1;
    } while (value != 0);

    size_t length = required - position;
    for (size_t i = 0; i < length; ++i) {
        buffer[i] = buffer[position + i];
    }

    return 1;
}

int main(void)
{
    enum {
        BINARY_SIZE = sizeof(unsigned long long) * CHAR_BIT + 1
    };

    char binary[BINARY_SIZE];
    char *line = NULL;
    size_t capacity = 0;
    char *end;
    unsigned long long value;

    if (getline(&line, &capacity, stdin) < 0) {
        free(line);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoull(line, &end, 10);

    if (errno == ERANGE || end == line) {
        free(line);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return EXIT_FAILURE;
    }

    if (!decimal_to_binary(value, binary, sizeof binary)) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);

    if (printf("%s\n", binary) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}