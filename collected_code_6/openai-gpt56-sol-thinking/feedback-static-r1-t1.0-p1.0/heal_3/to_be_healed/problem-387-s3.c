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
    size_t position = 0;
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
    size_t capacity,
    size_t *output_length)
{
    size_t length = 0;
    int line_terminated = 0;

    if (output == NULL || output_length == NULL || capacity == 0u) {
        return INPUT_ERROR;
    }

    while (!line_terminated) {
        unsigned char character;
        size_t bytes_read = fread(&character, sizeof character, 1u, stdin);

        if (bytes_read == 0u) {
            if (ferror(stdin) != 0) {
                return INPUT_ERROR;
            }

            if (length == 0u) {
                return INPUT_EMPTY;
            }

            break;
        }

        if (character == '\n') {
            line_terminated = 1;
            continue;
        }

        if (length >= capacity - 1u) {
            return INPUT_TOO_LONG;
        }

        output[length++] = character;
    }

    output[length] = '\0';
    *output_length = length;

    return INPUT_OK;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char input[MAX_INPUT_LENGTH + 1u];
    size_t input_length = 0;
    InputStatus input_status;
    HexParity parity;

    input_status = read_input_line(input, sizeof input, &input_length);

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

        return EXIT_FAILURE;
    }

    parity = check_hex_parity(input, input_length);

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