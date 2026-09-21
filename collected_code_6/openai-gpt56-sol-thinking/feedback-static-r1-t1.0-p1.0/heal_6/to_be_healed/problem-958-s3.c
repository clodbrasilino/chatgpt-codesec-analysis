#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define ROMAN_MAX_VALUE 3999
#define ROMAN_MAX_LENGTH 15
#define ROMAN_BUFFER_SIZE (ROMAN_MAX_LENGTH + 1)

typedef struct {
    int value;
    const char *numeral;
    size_t length;
} RomanMapping;

bool integer_to_roman(int value, char *buffer, size_t buffer_size)
{
    static const RomanMapping mappings[] = {
        {1000, "M", 1},
        {900, "CM", 2},
        {500, "D", 1},
        {400, "CD", 2},
        {100, "C", 1},
        {90, "XC", 2},
        {50, "L", 1},
        {40, "XL", 2},
        {10, "X", 1},
        {9, "IX", 2},
        {5, "V", 1},
        {4, "IV", 2},
        {1, "I", 1}
    };

    const size_t mapping_count = sizeof mappings / sizeof mappings[0];
    size_t position = 0;

    if (buffer == NULL || buffer_size == 0) {
        return false;
    }

    buffer[0] = '\0';

    if (value < 1 || value > ROMAN_MAX_VALUE) {
        return false;
    }

    for (size_t i = 0; i < mapping_count; ++i) {
        while (value >= mappings[i].value) {
            if (position >= buffer_size ||
                mappings[i].length >= buffer_size - position) {
                buffer[0] = '\0';
                return false;
            }

            for (size_t j = 0; j < mappings[i].length; ++j) {
                buffer[position++] = mappings[i].numeral[j];
            }

            value -= mappings[i].value;
        }
    }

    buffer[position] = '\0';
    return true;
}

int main(int argc, char *argv[])
{
    const char *program_name;
    char *end;
    long value;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char roman[ROMAN_BUFFER_SIZE];

    program_name =
        argc > 0 && argv[0] != NULL ? argv[0] : "roman";

    if (argc != 2 || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <integer from 1 to %d>\n",
                program_name, ROMAN_MAX_VALUE);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    value = strtol(argv[1], &end, 10);

    if (errno == ERANGE ||
        end == argv[1] ||
        end == NULL ||
        *end != '\0' ||
        value < 1 ||
        value > ROMAN_MAX_VALUE) {
        fprintf(stderr, "Invalid integer: expected a value from 1 to %d\n",
                ROMAN_MAX_VALUE);
        return EXIT_FAILURE;
    }

    if (!integer_to_roman((int)value, roman, sizeof roman)) {
        fprintf(stderr, "Failed to convert the integer to a Roman numeral\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", roman) < 0) {
        fprintf(stderr, "Failed to write output\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}