#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH 4095u

typedef enum {
    HEX_INVALID = -1,
    HEX_ODD = 0,
    HEX_EVEN = 1
} HexParity;

typedef enum {
    INPUT_OK,
    INPUT_EMPTY,
    INPUT_TOO_LONG,
    INPUT_ERROR
} InputStatus;

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

static HexParity check_hex_parity(const unsigned char *text, size_t length)
{
    size_t position = 0u;
    int last_digit = -1;

    if (text == NULL) {
        return HEX_INVALID;
    }

    while (position < length && isspace((int)text[position]) != 0) {
        ++position;
    }

    if (position < length &&
        (text[position] == '+' || text[position] == '-')) {
        ++position;
    }

    if (length - position >= 2u &&
        text[position] == '0' &&
        (text[position + 1u] == 'x' || text[position + 1u] == 'X')) {
        position += 2u;
    }

    while (position < length) {
        int value = hex_digit_value(text[position]);

        if (value < 0) {
            break;
        }

        last_digit = value;
        ++position;
    }

    if (last_digit < 0) {
        return HEX_INVALID;
    }

    while (position < length && isspace((int)text[position]) != 0) {
        ++position;
    }

    if (position != length) {
        return HEX_INVALID;
    }

    return (last_digit % 2 == 0) ? HEX_EVEN : HEX_ODD;
}

static InputStatus read_input_line(
    unsigned char *output,
    size_t output_capacity,
    size_t *output_length)
{
    size_t length = 0u;

    if (output == NULL || output_length == NULL || output_capacity == 0u) {
        return INPUT_ERROR;
    }

    output[0] = '\0';
    *output_length = 0u;

    for (;;) {
        int character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin) != 0) {
                return INPUT_ERROR;
            }

            if (length == 0u) {
                return INPUT_EMPTY;
            }

            break;
        }

        if (character == '\n') {
            break;
        }

        if (length == output_capacity - 1u) {
            int discarded_character;

            do {
                discarded_character = fgetc(stdin);
            } while (discarded_character != '\n' &&
                     discarded_character != EOF);

            if (discarded_character == EOF && ferror(stdin) != 0) {
                return INPUT_ERROR;
            }

            return INPUT_TOO_LONG;
        }

        output[length++] = (unsigned char)character;
    }

    output[length] = '\0';
    *output_length = length;

    return INPUT_OK;
}

int main(void)
{
    unsigned char *input;
    size_t input_length = 0u;
    InputStatus input_status;
    HexParity parity;
    int result = EXIT_FAILURE;

    input = malloc(MAX_INPUT_LENGTH + 1u);
    if (input == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    input_status = read_input_line(
        input,
        MAX_INPUT_LENGTH + 1u,
        &input_length
    );

    if (input_status != INPUT_OK) {
        switch (input_status) {
        case INPUT_EMPTY:
            fputs("No input provided\n", stderr);
            break;

        case INPUT_TOO_LONG:
            fputs("Input is too long\n", stderr);
            break;

        default:
            fputs("Input error\n", stderr);
            break;
        }

        free(input);
        return EXIT_FAILURE;
    }

    parity = check_hex_parity(input, input_length);

    if (parity == HEX_INVALID) {
        fputs("Invalid hexadecimal number\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (puts(parity == HEX_EVEN ? "Even" : "Odd") != EOF &&
        fflush(stdout) != EOF) {
        result = EXIT_SUCCESS;
    }

    free(input);
    return result;
}