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
    INPUT_ERROR,
    INPUT_NO_MEMORY
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

    while (position < length && isspace(text[position]) != 0) {
        ++position;
    }

    if (position < length &&
        (text[position] == '+' || text[position] == '-')) {
        ++position;
    }

    if (position + 1 < length &&
        text[position] == '0' &&
        (text[position + 1] == 'x' || text[position + 1] == 'X')) {
        position += 2;
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

    while (position < length && isspace(text[position]) != 0) {
        ++position;
    }

    if (position != length) {
        return HEX_INVALID;
    }

    return last_digit % 2 == 0 ? HEX_EVEN : HEX_ODD;
}

static InputStatus read_input_line(unsigned char **output, size_t *output_length)
{
    unsigned char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;

    if (output == NULL || output_length == NULL) {
        return INPUT_ERROR;
    }

    for (;;) {
        int character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin) != 0) {
                free(buffer);
                return INPUT_ERROR;
            }

            if (length == 0) {
                free(buffer);
                return INPUT_EMPTY;
            }

            break;
        }

        if (character == '\n') {
            break;
        }

        if (length >= MAX_INPUT_LENGTH) {
            free(buffer);
            return INPUT_TOO_LONG;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            unsigned char *new_buffer;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity > MAX_INPUT_LENGTH + 1u) {
                new_capacity = MAX_INPUT_LENGTH + 1u;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return INPUT_NO_MEMORY;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (unsigned char)character;
    }

    if (buffer == NULL) {
        buffer = malloc(1);
        if (buffer == NULL) {
            return INPUT_NO_MEMORY;
        }
        capacity = 1;
    }

    if (length >= capacity) {
        unsigned char *new_buffer = realloc(buffer, length + 1);

        if (new_buffer == NULL) {
            free(buffer);
            return INPUT_NO_MEMORY;
        }

        buffer = new_buffer;
    }

    buffer[length] = '\0';
    *output = buffer;
    *output_length = length;

    return INPUT_OK;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t input_length = 0;
    InputStatus input_status;
    HexParity parity;

    input_status = read_input_line(&input, &input_length);

    if (input_status != INPUT_OK) {
        switch (input_status) {
        case INPUT_EMPTY:
            fputs("No input provided\n", stderr);
            break;
        case INPUT_TOO_LONG:
            fputs("Input is too long\n", stderr);
            break;
        case INPUT_NO_MEMORY:
            fputs("Insufficient memory\n", stderr);
            break;
        default:
            fputs("Input error\n", stderr);
            break;
        }

        return EXIT_FAILURE;
    }

    parity = check_hex_parity(input, input_length);
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