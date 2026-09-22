#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *integer_to_roman(unsigned int value)
{
    static const struct {
        unsigned int value;
        const char *symbol;
        size_t length;
    } numerals[] = {
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

    enum { ROMAN_BUFFER_SIZE = 16 };
    char *result = malloc(ROMAN_BUFFER_SIZE);
    size_t position = 0U;
    size_t i;

    if (value == 0U || value > 3999U) {
        free(result);
        return NULL;
    }

    if (result == NULL) {
        return NULL;
    }

    for (i = 0U; i < sizeof numerals / sizeof numerals[0]; ++i) {
        while (value >= numerals[i].value) {
            size_t remaining = (size_t)ROMAN_BUFFER_SIZE - position;

            if (numerals[i].length >= remaining) {
                free(result);
                return NULL;
            }

            for (size_t j = 0U; j < numerals[i].length; ++j) {
                result[position++] = numerals[i].symbol[j];
            }

            value -= numerals[i].value;
        }
    }

    result[position] = '\0';
    return result;
}

int main(void)
{
    int input;
    char *roman;

    if (scanf("%d", &input) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (input < 1 || input > 3999) {
        fputs("Input must be between 1 and 3999\n", stderr);
        return EXIT_FAILURE;
    }

    roman = integer_to_roman((unsigned int)input);
    if (roman == NULL) {
        fputs("Conversion failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", roman) < 0) {
        free(roman);
        return EXIT_FAILURE;
    }

    free(roman);
    return EXIT_SUCCESS;
}