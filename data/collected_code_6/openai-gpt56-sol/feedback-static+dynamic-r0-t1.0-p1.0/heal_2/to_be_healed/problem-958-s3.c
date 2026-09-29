#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static char *integer_to_roman(unsigned int value)
{
    static const struct {
        unsigned int value;
        char first;
        char second;
    } numerals[] = {
        {1000U, 'M', '\0'}, {900U, 'C', 'M'}, {500U, 'D', '\0'},
        {400U, 'C', 'D'},   {100U, 'C', '\0'}, {90U, 'X', 'C'},
        {50U, 'L', '\0'},   {40U, 'X', 'L'},   {10U, 'X', '\0'},
        {9U, 'I', 'X'},     {5U, 'V', '\0'},   {4U, 'I', 'V'},
        {1U, 'I', '\0'}
    };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[16];
    size_t position = 0U;
    size_t i;
    char *result;

    if (value == 0U || value > 3999U) {
        return NULL;
    }

    for (i = 0U; i < sizeof numerals / sizeof numerals[0]; ++i) {
        while (value >= numerals[i].value) {
            size_t length = numerals[i].second == '\0' ? 1U : 2U;

            if (length > sizeof buffer - position - 1U) {
                return NULL;
            }

            buffer[position++] = numerals[i].first;
            if (numerals[i].second != '\0') {
                buffer[position++] = numerals[i].second;
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

    while (*end == ' ' || *end == '\t' || *end == '\r') {
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