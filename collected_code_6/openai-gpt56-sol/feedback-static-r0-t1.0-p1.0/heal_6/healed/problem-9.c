#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

static int minimum_rotations(const char *str, size_t length, size_t *result)
{
    size_t *prefix;
    size_t matched = 0;
    size_t period;

    if (str == NULL || result == NULL) {
        return 0;
    }

    if (length == 0) {
        *result = 0;
        return 1;
    }

    if (length > SIZE_MAX / sizeof(*prefix)) {
        return 0;
    }

    prefix = malloc(length * sizeof(*prefix));
    if (prefix == NULL) {
        return 0;
    }

    prefix[0] = 0;

    for (size_t i = 1; i < length; ++i) {
        while (matched > 0 && str[i] != str[matched]) {
            matched = prefix[matched - 1];
        }

        if (str[i] == str[matched]) {
            ++matched;
        }

        prefix[i] = matched;
    }

    period = length - prefix[length - 1];
    if (length % period != 0) {
        period = length;
    }

    free(prefix);
    *result = period;
    return 1;
}

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *resized;

    if (buffer == NULL || *buffer == NULL || capacity == NULL) {
        return 0;
    }

    if (required <= *capacity) {
        return 1;
    }

    new_capacity = *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = SIZE_MAX;
        } else {
            new_capacity *= 2;
        }

        if (new_capacity < required && new_capacity == SIZE_MAX) {
            return 0;
        }
    }

    resized = realloc(*buffer, new_capacity);
    if (resized == NULL) {
        return 0;
    }

    *buffer = resized;
    *capacity = new_capacity;
    return 1;
}

static int read_line(FILE *stream, char **buffer, size_t *length)
{
    char *data;
    size_t capacity = 64;
    size_t used = 0;

    if (stream == NULL || buffer == NULL || length == NULL) {
        return 0;
    }

    *buffer = NULL;
    *length = 0;

    data = malloc(capacity);
    if (data == NULL) {
        return 0;
    }

    for (;;) {
        int character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream)) {
                free(data);
                return 0;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (used > SIZE_MAX - 2) {
            free(data);
            return 0;
        }

        if (!grow_buffer(&data, &capacity, used + 2)) {
            free(data);
            return 0;
        }

        data[used++] = (char)(unsigned char)character;
    }

    if (used > 0 && data[used - 1] == '\r') {
        --used;
    }

    data[used] = '\0';
    *buffer = data;
    *length = used;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t rotations = 0;
    int status = EXIT_FAILURE;

    if (!read_line(stdin, &input, &length)) {
        goto cleanup;
    }

    if (!minimum_rotations(input, length, &rotations)) {
        goto cleanup;
    }

    if (printf("%zu\n", rotations) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}