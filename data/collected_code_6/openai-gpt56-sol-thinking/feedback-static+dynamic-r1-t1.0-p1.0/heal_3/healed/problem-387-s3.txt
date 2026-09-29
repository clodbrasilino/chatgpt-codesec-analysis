#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    HEX_INVALID = -1,
    HEX_ODD = 0,
    HEX_EVEN = 1
} HexParity;

typedef enum {
    READ_OK,
    READ_NO_INPUT,
    READ_TOO_LONG,
    READ_INVALID_DATA,
    READ_MEMORY_ERROR,
    READ_IO_ERROR
} ReadResult;

enum {
    MAX_INPUT_LENGTH = 4095
};

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

static HexParity check_hex_parity(const char *text)
{
    const unsigned char *current;
    int last_digit = -1;

    if (text == NULL) {
        return HEX_INVALID;
    }

    current = (const unsigned char *)text;

    while (isspace(*current)) {
        ++current;
    }

    if (*current == '+' || *current == '-') {
        ++current;
    }

    if (current[0] == '0' &&
        (current[1] == 'x' || current[1] == 'X')) {
        current += 2;
    }

    while (*current != '\0') {
        int digit = hex_digit_value(*current);

        if (digit < 0) {
            break;
        }

        last_digit = digit;
        ++current;
    }

    if (last_digit < 0) {
        return HEX_INVALID;
    }

    while (isspace(*current)) {
        ++current;
    }

    if (*current != '\0') {
        return HEX_INVALID;
    }

    return (last_digit % 2 == 0) ? HEX_EVEN : HEX_ODD;
}

static ReadResult read_input_line(FILE *stream, char **output)
{
    char *buffer;
    size_t length = 0;
    bool received_input = false;

    if (stream == NULL || output == NULL) {
        return READ_INVALID_DATA;
    }

    *output = NULL;

    buffer = malloc((size_t)MAX_INPUT_LENGTH + 1U);
    if (buffer == NULL) {
        return READ_MEMORY_ERROR;
    }

    for (;;) {
        unsigned char character;
        size_t bytes_read = fread(&character, 1U, 1U, stream);

        if (bytes_read == 0U) {
            if (ferror(stream)) {
                free(buffer);
                return READ_IO_ERROR;
            }
            break;
        }

        received_input = true;

        if (character == (unsigned char)'\n') {
            break;
        }

        if (character == (unsigned char)'\0') {
            free(buffer);
            return READ_INVALID_DATA;
        }

        if (length == (size_t)MAX_INPUT_LENGTH) {
            free(buffer);
            return READ_TOO_LONG;
        }

        buffer[length++] = (char)character;
    }

    if (!received_input) {
        free(buffer);
        return READ_NO_INPUT;
    }

    buffer[length] = '\0';
    *output = buffer;

    return READ_OK;
}

int main(void)
{
    char *input = NULL;
    ReadResult result;
    HexParity parity;

    result = read_input_line(stdin, &input);

    switch (result) {
        case READ_OK:
            break;

        case READ_NO_INPUT:
            fputs("No input provided\n", stderr);
            return EXIT_FAILURE;

        case READ_TOO_LONG:
            fputs("Input is too long\n", stderr);
            return EXIT_FAILURE;

        case READ_INVALID_DATA:
            fputs("Invalid hexadecimal number\n", stderr);
            return EXIT_FAILURE;

        case READ_MEMORY_ERROR:
            fputs("Memory allocation error\n", stderr);
            return EXIT_FAILURE;

        case READ_IO_ERROR:
        default:
            fputs("Input error\n", stderr);
            return EXIT_FAILURE;
    }

    parity = check_hex_parity(input);
    free(input);

    if (parity == HEX_INVALID) {
        fputs("Invalid hexadecimal number\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(parity == HEX_EVEN ? "Even" : "Odd") == EOF) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}