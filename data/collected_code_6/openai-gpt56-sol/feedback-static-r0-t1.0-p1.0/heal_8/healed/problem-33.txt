#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static char *decimal_to_binary(unsigned long long value)
{
    const size_t capacity = sizeof(value) * CHAR_BIT + 1;
    char *buffer = malloc(capacity);
    size_t position = capacity - 1;

    if (buffer == NULL) {
        return NULL;
    }

    buffer[position] = '\0';

    do {
        buffer[--position] = (char)('0' + (value & 1ULL));
        value >>= 1;
    } while (value != 0);

    {
        size_t length = capacity - position;
        char *result = malloc(length);

        if (result == NULL) {
            free(buffer);
            return NULL;
        }

        for (size_t i = 0; i < length; ++i) {
            result[i] = buffer[position + i];
        }

        free(buffer);
        return result;
    }
}

int main(void)
{
    char *input = NULL;
    char *start;
    char *end;
    char *binary;
    size_t capacity = 0;
    ssize_t length;
    unsigned long long value;

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

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    binary = decimal_to_binary(value);
    free(input);

    if (binary == NULL) {
        return EXIT_FAILURE;
    }

    if (printf("%s\n", binary) < 0) {
        free(binary);
        return EXIT_FAILURE;
    }

    free(binary);
    return EXIT_SUCCESS;
}