#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int decimal_to_binary(unsigned long long value, char *buffer, size_t size)
{
    size_t position;

    if (buffer == NULL || size == 0) {
        return 0;
    }

    position = size;
    buffer[--position] = '\0';

    do {
        if (position == 0) {
            return 0;
        }

        buffer[--position] = (char)('0' + (value & 1ULL));
        value >>= 1;
    } while (value != 0);

    {
        size_t length = size - position;
        size_t i;

        for (i = 0; i < length; ++i) {
            buffer[i] = buffer[position + i];
        }
    }

    return 1;
}

int main(void)
{
    char *binary = NULL;
    char *line = NULL;
    char *end = NULL;
    size_t capacity = 0;
    size_t binary_size = sizeof(unsigned long long) * CHAR_BIT + 1;
    unsigned long long value;
    int status = EXIT_FAILURE;

    if (getline(&line, &capacity, stdin) < 0) {
        goto cleanup;
    }

    errno = 0;
    value = strtoull(line, &end, 10);

    if (errno == ERANGE || end == line) {
        goto cleanup;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        goto cleanup;
    }

    binary = malloc(binary_size);
    if (binary == NULL) {
        goto cleanup;
    }

    if (!decimal_to_binary(value, binary, binary_size)) {
        goto cleanup;
    }

    if (printf("%s\n", binary) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(binary);
    free(line);
    return status;
}