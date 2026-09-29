#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int minimum_rotations(const unsigned char *string, size_t length,
                             size_t *result)
{
    size_t *prefix;
    size_t period;

    if (result == NULL) {
        return -1;
    }

    if (length == 0) {
        *result = 0;
        return 0;
    }

    if (string == NULL || length > SIZE_MAX / sizeof(*prefix)) {
        return -1;
    }

    prefix = malloc(length * sizeof(*prefix));
    if (prefix == NULL) {
        return -1;
    }

    prefix[0] = 0;

    for (size_t i = 1; i < length; ++i) {
        size_t matched = prefix[i - 1];

        while (matched > 0 && string[i] != string[matched]) {
            matched = prefix[matched - 1];
        }

        if (string[i] == string[matched]) {
            ++matched;
        }

        prefix[i] = matched;
    }

    period = length - prefix[length - 1];
    *result = length % period == 0 ? period : length;

    free(prefix);
    return 0;
}

static int append_bytes(unsigned char **buffer, size_t *length,
                        size_t *capacity, const unsigned char *source,
                        size_t count)
{
    size_t required;
    size_t new_capacity;
    unsigned char *new_buffer;

    if (buffer == NULL || length == NULL || capacity == NULL ||
        (source == NULL && count != 0) || count > SIZE_MAX - *length) {
        return -1;
    }

    required = *length + count;

    if (required > *capacity) {
        new_capacity = *capacity == 0 ? 64 : *capacity;

        while (new_capacity < required) {
            if (new_capacity > SIZE_MAX / 2) {
                new_capacity = required;
                break;
            }
            new_capacity *= 2;
        }

        new_buffer = realloc(*buffer, new_capacity);
        if (new_buffer == NULL) {
            return -1;
        }

        *buffer = new_buffer;
        *capacity = new_capacity;
    }

    for (size_t i = 0; i < count; ++i) {
        (*buffer)[*length + i] = source[i];
    }

    *length = required;
    return 0;
}

int main(void)
{
    unsigned char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;
    size_t rotations;
    int character;

    while ((character = fgetc(stdin)) != EOF) {
        unsigned char byte;

        if (character == '\n') {
            break;
        }

        byte = (unsigned char)character;

        if (append_bytes(&buffer, &length, &capacity, &byte, 1) != 0) {
            free(buffer);
            return EXIT_FAILURE;
        }
    }

    if (ferror(stdin)) {
        free(buffer);
        return EXIT_FAILURE;
    }

    if (minimum_rotations(buffer, length, &rotations) != 0) {
        free(buffer);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", rotations) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);
    return EXIT_SUCCESS;
}