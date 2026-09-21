#include <stdbool.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH ((size_t)4095)

enum read_status {
    READ_OK,
    READ_END_OF_FILE,
    READ_IO_ERROR,
    READ_TOO_LONG,
    READ_INVALID_INPUT
};

static bool find_max_occurring_character(
    const char *string,
    unsigned char *result
)
{
    size_t frequencies[(size_t)UCHAR_MAX + 1U] = {0};
    const unsigned char *cursor;
    size_t maximum = 0U;

    if (string == NULL || result == NULL || string[0] == '\0') {
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
            return true;
        }

        ++cursor;
    }

    return false;
}

static enum read_status read_input_line(
    FILE *stream,
    char *buffer,
    size_t buffer_size
)
{
    size_t length = 0U;

    if (stream == NULL || buffer == NULL || buffer_size < 2U) {
        return READ_INVALID_INPUT;
    }

    buffer[0] = '\0';

    for (;;) {
        int character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream)) {
                return READ_IO_ERROR;
            }

            if (length == 0U) {
                return READ_END_OF_FILE;
            }

            break;
        }

        if (character == '\n') {
            break;
        }

        if (character == '\0') {
            return READ_INVALID_INPUT;
        }

        if (length >= buffer_size - 1U) {
            return READ_TOO_LONG;
        }

        buffer[length] = (char)(unsigned char)character;
        ++length;
        buffer[length] = '\0';
    }

    if (length > 0U && buffer[length - 1U] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    return READ_OK;
}

int main(void)
{
    char input[MAX_INPUT_LENGTH + 1U];
    unsigned char result;
    enum read_status status;

    status = read_input_line(stdin, input, sizeof input);

    switch (status) {
        case READ_OK:
            break;

        case READ_END_OF_FILE:
            fputs("Failed to read a string.\n", stderr);
            return EXIT_FAILURE;

        case READ_IO_ERROR:
            fputs("Failed while reading the string.\n", stderr);
            return EXIT_FAILURE;

        case READ_TOO_LONG:
            fputs("Input string is too long.\n", stderr);
            return EXIT_FAILURE;

        case READ_INVALID_INPUT:
            fputs("Input contains invalid data.\n", stderr);
            return EXIT_FAILURE;

        default:
            fputs("Unexpected input error.\n", stderr);
            return EXIT_FAILURE;
    }

    if (!find_max_occurring_character(input, &result)) {
        fputs("The string must not be empty.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%c\n", (int)result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}