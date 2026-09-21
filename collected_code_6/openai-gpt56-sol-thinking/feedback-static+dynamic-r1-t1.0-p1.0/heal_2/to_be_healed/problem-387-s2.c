#include <stdbool.h>
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

    *is_even = (last_value % 2) == 0;
    return 0;
}

static int read_input_line(FILE *stream, char **result)
{
    char *buffer;
    size_t length = 0;
    bool invalid = false;
    bool input_received = false;

    if (stream == NULL || result == NULL) {
        return -1;
    }

    buffer = malloc(MAX_INPUT_LENGTH + 1U);

    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream) != 0 || !input_received) {
                free(buffer);
                return -1;
            }

            break;
        }

        input_received = true;

        if (character == '\n') {
            break;
        }

        if (character == '\0') {
            invalid = true;
        }

        if (length < MAX_INPUT_LENGTH) {
            buffer[length++] = (char)character;
        } else {
            invalid = true;
        }
    }

    if (invalid) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';
    *result = buffer;
    return 0;
}

int main(void)
{
    char *input = NULL;
    bool is_even;

    if (read_input_line(stdin, &input) != 0) {
        return EXIT_FAILURE;
    }

    if (hexadecimal_is_even(input, &is_even) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    puts(is_even ? "Even" : "Odd");

    return EXIT_SUCCESS;
}