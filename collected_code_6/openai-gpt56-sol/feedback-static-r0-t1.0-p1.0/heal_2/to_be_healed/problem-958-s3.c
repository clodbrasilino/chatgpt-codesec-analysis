#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static char *integer_to_roman(unsigned int value)
{
    static const struct {
        unsigned int value;
        const char *symbol;
        size_t length;
    } numerals[] = {
        {1000U, "M", 1U}, {900U, "CM", 2U}, {500U, "D", 1U},
        {400U, "CD", 2U}, {100U, "C", 1U}, {90U, "XC", 2U},
        {50U, "L", 1U}, {40U, "XL", 2U}, {10U, "X", 1U},
        {9U, "IX", 2U}, {5U, "V", 1U}, {4U, "IV", 2U},
        {1U, "I", 1U}
    };
    enum { ROMAN_BUFFER_SIZE = 16 };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[ROMAN_BUFFER_SIZE];
    size_t position = 0U;
    size_t i;
    char *result;

    if (value == 0U || value > 3999U) {
        return NULL;
    }

    for (i = 0U; i < sizeof numerals / sizeof numerals[0]; ++i) {
        while (value >= numerals[i].value) {
            size_t j;

            if (numerals[i].length > sizeof buffer - position - 1U) {
                return NULL;
            }

            for (j = 0U; j < numerals[i].length; ++j) {
                buffer[position++] = numerals[i].symbol[j];
            }

            value -= numerals[i].value;
        }
    }

    buffer[position] = '\0';

    result = malloc(position + 1U);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0U; i <= position; ++i) {
        result[i] = buffer[i];
    }

    return result;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end;
    unsigned long parsed;
    char *roman;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = input;
    parsed = strtoul(input, &end, 10);

    if (end == input || errno == ERANGE || parsed > UINT_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (*end == '\r') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
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