#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool integer_to_roman(int value, char *buffer, size_t buffer_size)
{
    static const int values[] = {
        1000, 900, 500, 400, 100, 90, 50,
        40, 10, 9, 5, 4, 1
    };
    static const char *const symbols[] = {
        "M", "CM", "D", "CD", "C", "XC", "L",
        "XL", "X", "IX", "V", "IV", "I"
    };

    char result[16];
    size_t position = 0;

    if (value < 1 || value > 3999 || buffer == NULL || buffer_size == 0) {
        return false;
    }

    for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); ++i) {
        const size_t symbol_length = strlen(symbols[i]);

        while (value >= values[i]) {
            if (symbol_length >= sizeof(result) - position) {
                return false;
            }

            memcpy(result + position, symbols[i], symbol_length);
            position += symbol_length;
            value -= values[i];
        }
    }

    if (position >= buffer_size) {
        return false;
    }

    result[position] = '\0';
    memcpy(buffer, result, position + 1);

    return true;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
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
        fprintf(stderr, "Invalid integer: expected a value from 1 to 3999\n");
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