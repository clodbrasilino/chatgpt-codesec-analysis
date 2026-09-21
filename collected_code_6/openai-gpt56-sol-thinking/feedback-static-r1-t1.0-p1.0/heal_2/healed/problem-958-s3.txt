#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROMAN_MAX_VALUE 3999
#define ROMAN_BUFFER_SIZE 16

typedef struct {
    int value;
    const char *numeral;
} RomanMapping;

bool integer_to_roman(int value, char *buffer, size_t buffer_size)
{
    static const RomanMapping mappings[] = {
        {1000, "M"},
        {900, "CM"},
        {500, "D"},
        {400, "CD"},
        {100, "C"},
        {90, "XC"},
        {50, "L"},
        {40, "XL"},
        {10, "X"},
        {9, "IX"},
        {5, "V"},
        {4, "IV"},
        {1, "I"}
    };

    size_t position = 0;

    if (buffer == NULL || buffer_size == 0) {
        return false;
    }

    buffer[0] = '\0';

    if (value < 1 || value > ROMAN_MAX_VALUE) {
        return false;
    }

    for (size_t i = 0; i < sizeof mappings / sizeof mappings[0]; ++i) {
        const size_t numeral_length = strlen(mappings[i].numeral);

        while (value >= mappings[i].value) {
            if (position >= buffer_size ||
                numeral_length > buffer_size - position - 1) {
                buffer[0] = '\0';
                return false;
            }

            memcpy(buffer + position, mappings[i].numeral, numeral_length);
            position += numeral_length;
            value -= mappings[i].value;
        }
    }

    buffer[position] = '\0';
    return true;
}

int main(int argc, char *argv[])
{
    const char *program_name;
    char *end = NULL;
    char *roman = NULL;
    long value;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "roman";

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer from 1 to %d>\n",
                program_name, ROMAN_MAX_VALUE);
        return EXIT_FAILURE;
    }

    errno = 0;
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

    roman = malloc(ROMAN_BUFFER_SIZE);
    if (roman == NULL) {
        fprintf(stderr, "Failed to allocate output buffer\n");
        return EXIT_FAILURE;
    }

    if (!integer_to_roman((int)value, roman, ROMAN_BUFFER_SIZE)) {
        fprintf(stderr, "Failed to convert the integer to a Roman numeral\n");
        free(roman);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", roman) < 0) {
        fprintf(stderr, "Failed to write output\n");
        free(roman);
        return EXIT_FAILURE;
    }

    free(roman);
    return EXIT_SUCCESS;
}