#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define ROMAN_MAX_VALUE 3999
#define ROMAN_BUFFER_SIZE 16

typedef struct {
    int value;
    const char *numeral;
    size_t length;
} RomanMapping;

#define ROMAN_MAPPING(value, numeral) \
    { (value), (numeral), sizeof(numeral) - 1U }

bool integer_to_roman(int value, char *buffer, size_t buffer_size)
{
    static const RomanMapping mappings[] = {
        ROMAN_MAPPING(1000, "M"),
        ROMAN_MAPPING(900, "CM"),
        ROMAN_MAPPING(500, "D"),
        ROMAN_MAPPING(400, "CD"),
        ROMAN_MAPPING(100, "C"),
        ROMAN_MAPPING(90, "XC"),
        ROMAN_MAPPING(50, "L"),
        ROMAN_MAPPING(40, "XL"),
        ROMAN_MAPPING(10, "X"),
        ROMAN_MAPPING(9, "IX"),
        ROMAN_MAPPING(5, "V"),
        ROMAN_MAPPING(4, "IV"),
        ROMAN_MAPPING(1, "I")
    };
    const size_t mapping_count = sizeof(mappings) / sizeof(mappings[0]);
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
                buffer[position + j] = mappings[i].numeral[j];
            }

            position += mappings[i].length;
            value -= mappings[i].value;
        }
    }

    buffer[position] = '\0';
    return true;
}

#undef ROMAN_MAPPING

int main(int argc, char *argv[])
{
    char roman[ROMAN_BUFFER_SIZE];
    char *end = NULL;
    long value;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer from 1 to %d>\n",
                argv[0], ROMAN_MAX_VALUE);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtol(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        value < 1 || value > ROMAN_MAX_VALUE) {
        fprintf(stderr, "Invalid integer: expected a value from 1 to %d\n",
                ROMAN_MAX_VALUE);
        return EXIT_FAILURE;
    }

    if (!integer_to_roman((int)value, roman, sizeof(roman))) {
        fprintf(stderr, "Failed to convert the integer to a Roman numeral\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", roman) < 0) {
        fprintf(stderr, "Failed to write output\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}