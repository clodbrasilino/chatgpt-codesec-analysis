#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t get_rightmost_set_bit_position(uint32_t value)
{
    uint32_t position = 0U;

    while (value != 0U) {
        ++position;

        if ((value & UINT32_C(1)) != 0U) {
            return position;
        }

        value >>= 1U;
    }

    return 0U;
}

static bool read_line(char **line, size_t *length)
{
    size_t capacity = 128U;
    size_t used = 0U;
    char *buffer;
    int ch;

    if (line == NULL || length == NULL) {
        return false;
    }

    *line = NULL;
    *length = 0U;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return false;
    }

    while ((ch = fgetc(stdin)) != EOF) {
        if (used >= capacity - 1U) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return false;
            }

            new_capacity = capacity * 2U;
            new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return false;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[used] = (char)ch;
        ++used;

        if (ch == '\n') {
            break;
        }
    }

    if (ferror(stdin) || (ch == EOF && used == 0U)) {
        free(buffer);
        return false;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;

    return true;
}

static bool parse_uint32(const char *input, size_t length, uint32_t *value)
{
    size_t position = 0U;
    uint32_t result = 0U;
    bool has_digit = false;

    if (input == NULL || value == NULL) {
        return false;
    }

    while (position < length &&
           isspace((unsigned char)input[position]) != 0) {
        ++position;
    }

    if (position < length && input[position] == '+') {
        ++position;
    } else if (position < length && input[position] == '-') {
        return false;
    }

    while (position < length &&
           isdigit((unsigned char)input[position]) != 0) {
        uint32_t digit =
            (uint32_t)((unsigned char)input[position] - (unsigned char)'0');

        if (result > (UINT32_MAX - digit) / UINT32_C(10)) {
            return false;
        }

        result = result * UINT32_C(10) + digit;
        has_digit = true;
        ++position;
    }

    if (!has_digit) {
        return false;
    }

    while (position < length &&
           isspace((unsigned char)input[position]) != 0) {
        ++position;
    }

    if (position != length) {
        return false;
    }

    *value = result;
    return true;
}

int main(void)
{
    char *input = NULL;
    size_t input_length = 0U;
    uint32_t value;

    if (!read_line(&input, &input_length) ||
        !parse_uint32(input, input_length, &value)) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    printf("%" PRIu32 "\n", get_rightmost_set_bit_position(value));

    return EXIT_SUCCESS;
}