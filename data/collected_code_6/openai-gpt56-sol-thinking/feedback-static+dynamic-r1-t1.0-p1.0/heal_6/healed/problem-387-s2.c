#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_INPUT_LENGTH 1023U

static int hex_digit_value(unsigned char character)
{
    if (character >= '0' && character <= '9') {
        return (int)(character - '0');
    }

    if (character >= 'a' && character <= 'f') {
        return (int)(character - 'a') + 10;
    }

    if (character >= 'A' && character <= 'F') {
        return (int)(character - 'A') + 10;
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

    while (*cursor != '\0' && isspace(*cursor) != 0) {
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

    while (*cursor != '\0' && isspace(*cursor) != 0) {
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
    unsigned char character;

    if (stream == NULL || buffer == NULL || capacity < 2U) {
        return -1;
    }

    for (;;) {
        size_t count = fread(&character, sizeof(character), 1U, stream);

        if (count != 1U) {
            if (ferror(stream) != 0 || !received) {
                return -1;
            }

            break;
        }

        received = true;

        if (character == (unsigned char)'\n') {
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

        buffer[length++] = (char)character;
    }

    if (invalid) {
        return -1;
    }

    buffer[length] = '\0';
    return 0;
}

int main(void)
{
    char input[MAX_INPUT_LENGTH + 1U];
    bool is_even;

    if (read_input_line(stdin, input, sizeof(input)) != 0) {
        return EXIT_FAILURE;
    }

    if (hexadecimal_is_even(input, &is_even) != 0) {
        return EXIT_FAILURE;
    }

    if (puts(is_even ? "Even" : "Odd") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}