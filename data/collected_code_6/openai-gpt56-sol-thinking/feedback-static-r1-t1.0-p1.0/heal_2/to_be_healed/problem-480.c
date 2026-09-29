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
    READ_INVALID_INPUT,
    READ_NO_MEMORY
};

bool find_max_occurring_character(const char *string, unsigned char *result)
{
    size_t frequencies[(size_t)UCHAR_MAX + 1U] = {0};
    const unsigned char *cursor;
    size_t maximum = 0;

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

static enum read_status read_input_line(FILE *stream, char **line)
{
    char *buffer;
    size_t length = 0;
    int character = EOF;
    bool terminated_by_newline = false;

    if (stream == NULL || line == NULL) {
        return READ_INVALID_INPUT;
    }

    *line = NULL;

    buffer = malloc(MAX_INPUT_LENGTH + 1U);

    if (buffer == NULL) {
        return READ_NO_MEMORY;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stream);

        if (character == EOF) {
            break;
        }

        if (character == '\n') {
            terminated_by_newline = true;
            break;
        }

        if (character == '\0') {
            free(buffer);
            return READ_INVALID_INPUT;
        }

        if (length == MAX_INPUT_LENGTH) {
            free(buffer);
            return READ_TOO_LONG;
        }

        buffer[length++] = (char)(unsigned char)character;
    }

    if (character == EOF && ferror(stream)) {
        free(buffer);
        return READ_IO_ERROR;
    }

    if (character == EOF && length == 0) {
        free(buffer);
        return READ_END_OF_FILE;
    }

    if (terminated_by_newline && length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *line = buffer;

    return READ_OK;
}

int main(void)
{
    char *input = NULL;
    unsigned char result;
    enum read_status status;

    status = read_input_line(stdin, &input);

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

        case READ_NO_MEMORY:
            fputs("Unable to allocate memory.\n", stderr);
            return EXIT_FAILURE;

        default:
            fputs("Unexpected input error.\n", stderr);
            return EXIT_FAILURE;
    }

    if (!find_max_occurring_character(input, &result)) {
        fputs("The string must not be empty.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (printf("%c\n", (int)result) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}