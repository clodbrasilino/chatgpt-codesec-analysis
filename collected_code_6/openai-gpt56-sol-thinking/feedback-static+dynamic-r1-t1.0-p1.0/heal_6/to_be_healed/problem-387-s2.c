#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_INPUT_LENGTH 1023U

static int hex_digit_value(unsigned char character)
{
    if (character >= '0' && character <= '9') {
        return character - '0';
    }

    if (character >= 'a' && character <= 'f') {
        return character - 'a' + 10;
    }

    if (character >= 'A' && character <= 'F') {
        return character - 'A' + 10;
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

    while (isspace(*cursor) != 0) {
        ++cursor;
    }

    if (cursor[0] == '0' && (cursor[1] == 'x' || cursor[1] == 'X')) {
        cursor += 2;
    }

    while (*cursor != '\0') {
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

    while (isspace(*cursor) != 0) {
        ++cursor;
    }

    if (*cursor != '\0') {
        return -1;
    }

    *is_even = (last_value & 1) == 0;
    return 0;
}

static int read_input_line(FILE *stream, char *buffer, size_t capacity)
{
    size_t length = 0U;
    bool received = false;
    bool invalid = false;
    int character;

    if (stream == NULL || buffer == NULL || capacity < 2U) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder getc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getc(stream)) != EOF) {
        received = true;

        if (character == '\n') {
            break;
        }

        if (character == '\0') {
            invalid = true;
            continue;
        }

        if (length >= capacity - 1U) {
            invalid = true;
            continue;
        }

        buffer[length++] = (char)(unsigned char)character;
    }

    if (character == EOF && (ferror(stream) != 0 || !received)) {
        return -1;
    }

    if (invalid) {
        return -1;
    }

    buffer[length] = '\0';
    return 0;
}

int main(void)
{
    char *input;
    bool is_even;
    int result = EXIT_FAILURE;

    input = malloc(MAX_INPUT_LENGTH + 1U);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    if (read_input_line(stdin, input, MAX_INPUT_LENGTH + 1U) != 0) {
        goto cleanup;
    }

    if (hexadecimal_is_even(input, &is_even) != 0) {
        goto cleanup;
    }

    if (puts(is_even ? "Even" : "Odd") == EOF) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    free(input);
    return result;
}