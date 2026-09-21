#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROMAN_MAX_VALUE 3999U

typedef struct {
    unsigned int value;
    const char *symbol;
} RomanMapping;

static const RomanMapping roman_mappings[] = {
    {1000U, "M"},
    {900U, "CM"},
    {500U, "D"},
    {400U, "CD"},
    {100U, "C"},
    {90U, "XC"},
    {50U, "L"},
    {40U, "XL"},
    {10U, "X"},
    {9U, "IX"},
    {5U, "V"},
    {4U, "IV"},
    {1U, "I"}
};

static bool roman_length(unsigned int value, size_t *length)
{
    const size_t mapping_count =
        sizeof(roman_mappings) / sizeof(roman_mappings[0]);
    size_t required = 0U;

    if (length == NULL || value == 0U || value > ROMAN_MAX_VALUE) {
        return false;
    }

    for (size_t i = 0U; i < mapping_count; ++i) {
        const size_t symbol_length = strlen(roman_mappings[i].symbol);

        while (value >= roman_mappings[i].value) {
            required += symbol_length;
            value -= roman_mappings[i].value;
        }
    }

    *length = required;
    return true;
}

static bool integer_to_roman(unsigned int value, char *output,
                             size_t output_size)
{
    const size_t mapping_count =
        sizeof(roman_mappings) / sizeof(roman_mappings[0]);
    size_t required;
    size_t position = 0U;

    if (output == NULL || output_size == 0U) {
        return false;
    }

    output[0] = '\0';

    if (!roman_length(value, &required) || required >= output_size) {
        return false;
    }

    for (size_t i = 0U; i < mapping_count; ++i) {
        const size_t symbol_length = strlen(roman_mappings[i].symbol);

        while (value >= roman_mappings[i].value) {
            memcpy(output + position,
                   roman_mappings[i].symbol,
                   symbol_length);
            position += symbol_length;
            value -= roman_mappings[i].value;
        }
    }

    output[position] = '\0';
    return true;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    char *roman;
    unsigned long parsed_value;
    size_t required;

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

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        parsed_value == 0UL || parsed_value > ROMAN_MAX_VALUE) {
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