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

static HexParity check_hex_parity(
    const unsigned char *text,
    size_t length)
{
    size_t position = 0u;
    int last_digit = -1;

    if (text == NULL) {
        return HEX_INVALID;
    }

    while (position < length &&
           isspace((int)text[position]) != 0) {
        ++position;
    }

    if (position < length &&
        (text[position] == (unsigned char)'+' ||
         text[position] == (unsigned char)'-')) {
        ++position;
    }

    if (position < length &&
        length - position >= 2u &&
        text[position] == (unsigned char)'0' &&
        (text[position + 1u] == (unsigned char)'x' ||
         text[position + 1u] == (unsigned char)'X')) {
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

    while (position < length &&
           isspace((int)text[position]) != 0) {
        ++position;
    }

    if (position != length) {
        return HEX_INVALID;
    }

    return (last_digit % 2 == 0) ? HEX_EVEN : HEX_ODD;
}

static InputStatus discard_line(void)
{
    unsigned char character;

    while (fread(&character, sizeof character, 1u, stdin) == 1u) {
        if (character == (unsigned char)'\n') {
            return INPUT_OK;
        }
    }

    return ferror(stdin) != 0 ? INPUT_ERROR : INPUT_OK;
}

static InputStatus read_input_line(
    unsigned char *output,
    size_t output_capacity,
    size_t *output_length)
{
    size_t length = 0u;

    if (output == NULL ||
        output_length == NULL ||
        output_capacity == 0u) {
        return INPUT_ERROR;
    }

    output[0] = (unsigned char)'\0';
    *output_length = 0u;

    for (;;) {
        unsigned char character;
        size_t count = fread(
            &character,
            sizeof character,
            1u,
            stdin
        );

        if (count != 1u) {
            if (ferror(stdin) != 0) {
                return INPUT_ERROR;
            }

            if (length == 0u) {
                return INPUT_EMPTY;
            }

            break;
        }

        if (character == (unsigned char)'\n') {
            break;
        }

        if (length >= output_capacity - 1u) {
            InputStatus discard_status = discard_line();

            if (discard_status != INPUT_OK) {
                return discard_status;
            }

            return INPUT_TOO_LONG;
        }

        output[length] = character;
        ++length;
    }

    output[length] = (unsigned char)'\0';
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

    input = malloc((size_t)MAX_INPUT_LENGTH + 1u);
    if (input == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    input_status = read_input_line(
        input,
        (size_t)MAX_INPUT_LENGTH + 1u,
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

        case INPUT_ERROR:
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
        fflush(stdout) == 0) {
        result = EXIT_SUCCESS;
    }

    free(input);
    return result;
}