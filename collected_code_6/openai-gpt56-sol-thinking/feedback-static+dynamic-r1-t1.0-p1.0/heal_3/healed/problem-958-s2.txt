#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define ROMAN_MAX_VALUE 3999U

typedef struct {
    unsigned int value;
    char symbol[3];
    size_t symbol_length;
} RomanMapping;

static const RomanMapping roman_mappings[] = {
    {1000U, "M", 1U},
    {900U, "CM", 2U},
    {500U, "D", 1U},
    {400U, "CD", 2U},
    {100U, "C", 1U},
    {90U, "XC", 2U},
    {50U, "L", 1U},
    {40U, "XL", 2U},
    {10U, "X", 1U},
    {9U, "IX", 2U},
    {5U, "V", 1U},
    {4U, "IV", 2U},
    {1U, "I", 1U}
};

static bool roman_length(unsigned int value, size_t *length)
{
    const size_t mapping_count =
        sizeof roman_mappings / sizeof roman_mappings[0];
    size_t required = 0U;

    if (length == NULL || value == 0U || value > ROMAN_MAX_VALUE) {
        return false;
    }

    for (size_t i = 0U; i < mapping_count; ++i) {
        unsigned int repetitions = value / roman_mappings[i].value;

        required += (size_t)repetitions * roman_mappings[i].symbol_length;
        value %= roman_mappings[i].value;
    }

    *length = required;
    return true;
}

static bool integer_to_roman(unsigned int value, char *output,
                             size_t output_size)
{
    const size_t mapping_count =
        sizeof roman_mappings / sizeof roman_mappings[0];
    size_t required = 0U;
    size_t position = 0U;

    if (output == NULL || output_size == 0U) {
        return false;
    }

    output[0] = '\0';

    if (!roman_length(value, &required) ||
        required > output_size - 1U) {
        return false;
    }

    for (size_t i = 0U; i < mapping_count; ++i) {
        while (value >= roman_mappings[i].value) {
            if (roman_mappings[i].symbol_length >
                output_size - position - 1U) {
                output[0] = '\0';
                return false;
            }

            for (size_t j = 0U;
                 j < roman_mappings[i].symbol_length;
                 ++j) {
                output[position++] = roman_mappings[i].symbol[j];
            }

            value -= roman_mappings[i].value;
        }
    }

    output[position] = '\0';
    return true;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    char *roman = NULL;
    unsigned long parsed_value;
    size_t required = 0U;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer from 1 to 3999>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1][0] < '0' || argv[1][0] > '9') {
        fputs("Invalid integer: expected a value from 1 to 3999\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_value = strtoul(argv[1], &end, 10);

    if (errno == ERANGE ||
        end == argv[1] ||
        *end != '\0' ||
        parsed_value == 0UL ||
        parsed_value > (unsigned long)ROMAN_MAX_VALUE) {
        fputs("Invalid integer: expected a value from 1 to 3999\n", stderr);
        return EXIT_FAILURE;
    }

    if (!roman_length((unsigned int)parsed_value, &required)) {
        fputs("Failed to determine output size\n", stderr);
        return EXIT_FAILURE;
    }

    roman = malloc(required + 1U);
    if (roman == NULL) {
        fputs("Failed to allocate output buffer\n", stderr);
        return EXIT_FAILURE;
    }

    if (!integer_to_roman((unsigned int)parsed_value,
                          roman,
                          required + 1U)) {
        fputs("Failed to convert the integer\n", stderr);
        free(roman);
        return EXIT_FAILURE;
    }

    puts(roman);
    free(roman);

    return EXIT_SUCCESS;
}