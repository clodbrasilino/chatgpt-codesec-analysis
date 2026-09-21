#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct roman_token {
    int value;
    char first;
    char second;
};

static bool integer_to_roman(int value, char *buffer, size_t buffer_size)
{
    static const struct roman_token tokens[] = {
        {1000, 'M', '\0'},
        {900,  'C', 'M'},
        {500,  'D', '\0'},
        {400,  'C', 'D'},
        {100,  'C', '\0'},
        {90,   'X', 'C'},
        {50,   'L', '\0'},
        {40,   'X', 'L'},
        {10,   'X', '\0'},
        {9,    'I', 'X'},
        {5,    'V', '\0'},
        {4,    'I', 'V'},
        {1,    'I', '\0'}
    };

    const size_t token_count = sizeof tokens / sizeof tokens[0];
    size_t required = 0;
    size_t position = 0;
    int remaining;

    if (value < 1 || value > 3999 || buffer == NULL) {
        return false;
    }

    remaining = value;

    for (size_t i = 0; i < token_count; ++i) {
        const size_t count = (size_t)(remaining / tokens[i].value);
        const size_t symbol_length =
            tokens[i].second == '\0' ? 1U : 2U;

        required += count * symbol_length;
        remaining %= tokens[i].value;
    }

    if (buffer_size <= required) {
        return false;
    }

    remaining = value;

    for (size_t i = 0; i < token_count; ++i) {
        while (remaining >= tokens[i].value) {
            buffer[position++] = tokens[i].first;

            if (tokens[i].second != '\0') {
                buffer[position++] = tokens[i].second;
            }

            remaining -= tokens[i].value;
        }
    }

    buffer[position] = '\0';
    return true;
}

int main(int argc, char * const argv[])
{
    const size_t roman_capacity = sizeof "MMMDCCCLXXXVIII";
    const char *input;
    char *end = NULL;
    char *roman;
    long value;
    int status = EXIT_SUCCESS;

    if (argc != 2) {
        fputs("Usage: program <integer from 1 to 3999>\n", stderr);
        return EXIT_FAILURE;
    }

    input = argv[1];
    errno = 0;
    value = strtol(input, &end, 10);

    if (errno == ERANGE || end == input || *end != '\0' ||
        value < 1 || value > 3999) {
        fputs("Invalid integer: expected a value from 1 to 3999\n", stderr);
        return EXIT_FAILURE;
    }

    roman = malloc(roman_capacity);

    if (roman == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (!integer_to_roman((int)value, roman, roman_capacity)) {
        fputs("Roman numeral conversion failed\n", stderr);
        status = EXIT_FAILURE;
    } else if (printf("%s\n", roman) < 0) {
        status = EXIT_FAILURE;
    }

    free(roman);
    return status;
}