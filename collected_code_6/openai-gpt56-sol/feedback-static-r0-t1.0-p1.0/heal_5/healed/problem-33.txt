#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static int decimal_to_binary(unsigned long long value, char *buffer, size_t size)
{
    const size_t required = sizeof(value) * CHAR_BIT + 1;
    size_t position = required - 1;

    if (buffer == NULL || size < required) {
        return 0;
    }

    buffer[position] = '\0';

    do {
        buffer[--position] = (char)('0' + (value & 1ULL));
        value >>= 1;
    } while (value != 0);

    if (position != 0) {
        size_t source = position;
        size_t destination = 0;

        do {
            buffer[destination++] = buffer[source];
        } while (buffer[source++] != '\0');
    }

    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    char binary[sizeof(unsigned long long) * CHAR_BIT + 1];
    char *start;
    char *end;
    unsigned long long value;
    ssize_t length;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    while (length > 0 &&
           (input[length - 1] == '\n' || input[length - 1] == '\r')) {
        input[--length] = '\0';
    }

    start = input;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start) {
        free(input);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' ||
        !decimal_to_binary(value, binary, sizeof binary)) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%s\n", binary) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}