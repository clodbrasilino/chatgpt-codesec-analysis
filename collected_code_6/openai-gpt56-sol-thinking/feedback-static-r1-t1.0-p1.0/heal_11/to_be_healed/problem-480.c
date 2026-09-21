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
    const unsigned char *string,
    unsigned char *result
)
{
    size_t frequencies[(size_t)UCHAR_MAX + 1U] = {0U};
    size_t maximum = 0U;
    size_t index;

    if (string == NULL || result == NULL || string[0] == '\0') {
        return false;
    }

    for (index = 0U; string[index] != '\0'; ++index) {
        unsigned char character = string[index];

        ++frequencies[character];

        if (frequencies[character] > maximum) {
            maximum = frequencies[character];
        }
    }

    for (index = 0U; string[index] != '\0'; ++index) {
        unsigned char character = string[index];

        if (frequencies[character] == maximum) {
            *result = character;
            return true;
        }
    }

    return false;
}

static enum read_status read_input_line(
    FILE *stream,
    unsigned char *buffer,
    size_t buffer_size
)
{
    size_t length = 0U;
    size_t capacity;

    if (stream == NULL || buffer == NULL || buffer_size < 2U) {
        return READ_INVALID_INPUT;
    }

    capacity = buffer_size - 1U;
    buffer[0] = '\0';

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int input = fgetc(stream);

        if (input == EOF) {
            if (ferror(stream)) {
                buffer[length] = '\0';
                return READ_IO_ERROR;
            }

            if (length == 0U) {
                return READ_END_OF_FILE;
            }

            break;
        }

        if (input == '\0') {
            buffer[length] = '\0';
            return READ_INVALID_INPUT;
        }

        if (input == '\n') {
            break;
        }

        if (length >= capacity) {
            buffer[length] = '\0';
            return READ_TOO_LONG;
        }

        buffer[length++] = (unsigned char)input;
    }

    if (length > 0U && buffer[length - 1U] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    return READ_OK;
}

int main(void)
{
    unsigned char *input;
    unsigned char result;
    enum read_status status;
    int exit_status = EXIT_FAILURE;

    input = malloc(MAX_INPUT_LENGTH + 1U);
    if (input == NULL) {
        fputs("Failed to allocate input buffer.\n", stderr);
        return EXIT_FAILURE;
    }

    status = read_input_line(stdin, input, MAX_INPUT_LENGTH + 1U);

    switch (status) {
        case READ_OK:
            break;

        case READ_END_OF_FILE:
            fputs("Failed to read a string.\n", stderr);
            goto cleanup;

        case READ_IO_ERROR:
            fputs("Failed while reading the string.\n", stderr);
            goto cleanup;

        case READ_TOO_LONG:
            fputs("Input string is too long.\n", stderr);
            goto cleanup;

        case READ_INVALID_INPUT:
            fputs("Input contains invalid data.\n", stderr);
            goto cleanup;

        default:
            fputs("Unexpected input error.\n", stderr);
            goto cleanup;
    }

    if (!find_max_occurring_character(input, &result)) {
        fputs("The string must not be empty.\n", stderr);
        goto cleanup;
    }

    if (printf("%c\n", (int)result) < 0) {
        fputs("Failed to write the result.\n", stderr);
        goto cleanup;
    }

    exit_status = EXIT_SUCCESS;

cleanup:
    free(input);
    return exit_status;
}