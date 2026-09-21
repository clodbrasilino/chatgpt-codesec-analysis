#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_INPUT_LENGTH 1023U

static int hex_digit_value(unsigned char character)
{
    if (character >= (unsigned char)'0' &&
        character <= (unsigned char)'9') {
        return (int)(character - (unsigned char)'0');
    }

    if (character >= (unsigned char)'a' &&
        character <= (unsigned char)'f') {
        return (int)(character - (unsigned char)'a') + 10;
    }

    if (character >= (unsigned char)'A' &&
        character <= (unsigned char)'F') {
        return (int)(character - (unsigned char)'A') + 10;
    }

    return -1;
}

static int hexadecimal_is_even(const char *text, bool *is_even)
{
    const unsigned char *cursor;
    int last_value = -1;

    if (text == NULL || is_even == NULL) {
        return -1;
    }

    cursor = (const unsigned char *)text;

    while (*cursor != (unsigned char)'\0' && isspace(*cursor) != 0) {
        ++cursor;
    }

    if (cursor[0] == (unsigned char)'0' &&
        (cursor[1] == (unsigned char)'x' ||
         cursor[1] == (unsigned char)'X')) {
        cursor += 2;
    }

    while (*cursor != (unsigned char)'\0') {
        int value = hex_digit_value(*cursor);

        if (value < 0) {
            break;
        }

        last_value = value;
        ++cursor;
    }

    if (last_value < 0) {
        return -1;
    }

    while (*cursor != (unsigned char)'\0' && isspace(*cursor) != 0) {
        ++cursor;
    }

    if (*cursor != (unsigned char)'\0') {
        return -1;
    }

    *is_even = (last_value & 1) == 0;
    return 0;
}

static int read_input_line(FILE *stream, char **output)
{
    char *buffer;
    size_t length = 0U;
    bool received = false;
    bool invalid = false;
    int input;

    if (stream == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;

    buffer = malloc((size_t)MAX_INPUT_LENGTH + 1U);
    if (buffer == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((input = fgetc(stream)) != EOF) {
        received = true;

        if (input == '\n') {
            break;
        }

        if (input == '\0') {
            invalid = true;
            continue;
        }

        if (length >= (size_t)MAX_INPUT_LENGTH) {
            invalid = true;
            continue;
        }

        buffer[length++] = (char)(unsigned char)input;
    }

    if ((input == EOF && (ferror(stream) != 0 || !received)) || invalid) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';
    *output = buffer;
    return 0;
}

int main(void)
{
    char *input = NULL;
    bool is_even;
    int status = EXIT_FAILURE;

    if (read_input_line(stdin, &input) != 0) {
        goto cleanup;
    }

    if (hexadecimal_is_even(input, &is_even) != 0) {
        goto cleanup;
    }

    if (puts(is_even ? "Even" : "Odd") == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}