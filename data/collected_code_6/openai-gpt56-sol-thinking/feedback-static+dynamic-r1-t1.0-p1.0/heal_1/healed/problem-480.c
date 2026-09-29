#include <stdbool.h>
#include <limits.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum read_status {
    READ_STATUS_OK,
    READ_STATUS_EOF,
    READ_STATUS_ERROR,
    READ_STATUS_INVALID,
    READ_STATUS_NO_MEMORY
};

static enum read_status read_line(FILE *stream, char **line)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;
    int character;

    if (stream == NULL || line == NULL) {
        return READ_STATUS_INVALID;
    }

    *line = NULL;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return READ_STATUS_NO_MEMORY;
    }

    while ((character = fgetc(stream)) != '\n' && character != EOF) {
        char *resized;

        if (character == '\0') {
            free(buffer);
            return READ_STATUS_INVALID;
        }

        if (length == capacity - 1) {
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return READ_STATUS_NO_MEMORY;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);

            if (resized == NULL) {
                free(buffer);
                return READ_STATUS_NO_MEMORY;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)character;
    }

    if (character == EOF) {
        if (ferror(stream)) {
            free(buffer);
            return READ_STATUS_ERROR;
        }

        if (length == 0) {
            free(buffer);
            return READ_STATUS_EOF;
        }
    } else if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *line = buffer;

    return READ_STATUS_OK;
}

bool find_max_occurring_character(const char *string, unsigned char *result)
{
    const size_t frequency_count = (size_t)UCHAR_MAX + 1;
    size_t *frequencies;
    const unsigned char *cursor;
    size_t maximum = 0;

    if (string == NULL || result == NULL || string[0] == '\0') {
        return false;
    }

    frequencies = calloc(frequency_count, sizeof(*frequencies));

    if (frequencies == NULL) {
        return false;
    }

    cursor = (const unsigned char *)string;

    while (*cursor != '\0') {
        ++frequencies[*cursor];

        if (frequencies[*cursor] > maximum) {
            maximum = frequencies[*cursor];
        }

        ++cursor;
    }

    cursor = (const unsigned char *)string;

    while (*cursor != '\0') {
        if (frequencies[*cursor] == maximum) {
            *result = *cursor;
            free(frequencies);
            return true;
        }

        ++cursor;
    }

    free(frequencies);
    return false;
}

int main(void)
{
    char *input = NULL;
    unsigned char result;
    enum read_status status;

    status = read_line(stdin, &input);

    if (status != READ_STATUS_OK) {
        switch (status) {
            case READ_STATUS_EOF:
                fputs("Failed to read a string.\n", stderr);
                break;
            case READ_STATUS_ERROR:
                fputs("Failed while reading the string.\n", stderr);
                break;
            case READ_STATUS_INVALID:
                fputs("Input contains invalid data.\n", stderr);
                break;
            case READ_STATUS_NO_MEMORY:
                fputs("Insufficient memory.\n", stderr);
                break;
            case READ_STATUS_OK:
                break;
        }

        return EXIT_FAILURE;
    }

    if (!find_max_occurring_character(input, &result)) {
        if (input[0] == '\0') {
            fputs("The string must not be empty.\n", stderr);
        } else {
            fputs("Unable to process the string.\n", stderr);
        }

        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%c\n", (int)result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}