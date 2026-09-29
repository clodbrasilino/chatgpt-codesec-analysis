#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool integer_to_roman(int value, char *buffer, size_t buffer_size)
{
    static const struct {
        int value;
        const char *symbol;
        size_t length;
    } numerals[] = {
        {1000, "M",  1},
        {900,  "CM", 2},
        {500,  "D",  1},
        {400,  "CD", 2},
        {100,  "C",  1},
        {90,   "XC", 2},
        {50,   "L",  1},
        {40,   "XL", 2},
        {10,   "X",  1},
        {9,    "IX", 2},
        {5,    "V",  1},
        {4,    "IV", 2},
        {1,    "I",  1}
    };

    char result[16];
    size_t position = 0;

    if (buffer == NULL || buffer_size == 0) {
        return false;
    }

    buffer[0] = '\0';

    if (value < 1 || value > 3999) {
        return false;
    }

    for (size_t i = 0; i < sizeof(numerals) / sizeof(numerals[0]); ++i) {
        while (value >= numerals[i].value) {
            if (numerals[i].length >= sizeof(result) - position) {
                return false;
            }

            memcpy(result + position, numerals[i].symbol, numerals[i].length);
            position += numerals[i].length;
            value -= numerals[i].value;
        }
    }

    if (position >= buffer_size) {
        return false;
    }

    result[position] = '\0';
    memcpy(buffer, result, position + 1);

    return true;
}

int main(int argc, char *argv[const])
{
    char *end = NULL;
    char roman[16];
    long value;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer from 1 to 3999>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "roman");
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtol(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        value < 1 || value > 3999) {
        fprintf(stderr,
                "Invalid integer: expected a value from 1 to 3999\n");
        return EXIT_FAILURE;
    }

    if (!integer_to_roman((int)value, roman, sizeof(roman))) {
        fprintf(stderr, "Roman numeral conversion failed\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", roman) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}