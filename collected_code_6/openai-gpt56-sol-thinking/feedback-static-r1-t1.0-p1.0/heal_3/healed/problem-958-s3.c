#include <errno.h>
#include <limits.h>
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

static bool integer_to_roman(int value, char *buffer, size_t buffer_size)
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
            if (numeral_length >= buffer_size - position) {
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

static int run(int argc, const char *program_name, const char *argument)
{
    char *end = NULL;
    char roman[ROMAN_BUFFER_SIZE];
    long value;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer from 1 to %d>\n",
                program_name, ROMAN_MAX_VALUE);
        return EXIT_FAILURE;
    }

    if (argument == NULL) {
        fprintf(stderr, "Invalid integer: expected a value from 1 to %d\n",
                ROMAN_MAX_VALUE);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtol(argument, &end, 10);

    if (errno == ERANGE ||
        end == argument ||
        *end != '\0' ||
        value < 1 ||
        value > ROMAN_MAX_VALUE ||
        value > INT_MAX) {
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

int main(int argc, char *argv[])
{
    const char *program_name = "roman";
    const char *argument = NULL;

    if (argc > 0 && argv[0] != NULL) {
        program_name = argv[0];
    }

    if (argc > 1) {
        argument = argv[1];
    }

    return run(argc, program_name, argument);
}