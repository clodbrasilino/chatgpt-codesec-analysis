#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static char *integer_to_roman(unsigned int value)
{
    static const struct {
        unsigned int value;
        const char *symbol;
    } numerals[] = {
        {1000U, "M"}, {900U, "CM"}, {500U, "D"}, {400U, "CD"},
        {100U, "C"},  {90U, "XC"},  {50U, "L"},  {40U, "XL"},
        {10U, "X"},   {9U, "IX"},   {5U, "V"},   {4U, "IV"},
        {1U, "I"}
    };
    char *result;
    size_t position = 0U;
    size_t i;
    const size_t capacity = 16U;

    if (value == 0U || value > 3999U) {
        return NULL;
    }

    result = malloc(capacity);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0U; i < sizeof numerals / sizeof numerals[0]; ++i) {
        while (value >= numerals[i].value) {
            const char *symbol = numerals[i].symbol;

            while (*symbol != '\0') {
                if (position + 1U >= capacity) {
                    free(result);
                    return NULL;
                }

                result[position++] = *symbol++;
            }

            value -= numerals[i].value;
        }
    }

    result[position] = '\0';
    return result;
}

int main(void)
{
    char input[128];
    char *end;
    unsigned long parsed;
    char *roman;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    end = input;
    while (*end != '\0' && *end != '\n') {
        ++end;
    }

    if (*end != '\n' && !feof(stdin)) {
        int character;

        do {
            character = getchar();
        } while (character != '\n' && character != EOF);

        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    *end = '\0';

    errno = 0;
    end = input;
    parsed = strtoul(input, &end, 10);

    if (end == input || errno == ERANGE || parsed > UINT_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    roman = integer_to_roman((unsigned int)parsed);
    if (roman == NULL) {
        fputs("Value must be between 1 and 3999\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", roman) < 0) {
        free(roman);
        return EXIT_FAILURE;
    }

    free(roman);
    return EXIT_SUCCESS;
}