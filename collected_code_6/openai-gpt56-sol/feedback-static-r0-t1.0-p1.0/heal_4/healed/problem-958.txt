#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *integer_to_roman(unsigned int value)
{
    static const struct {
        unsigned int value;
        const char *symbol;
        size_t length;
    } numerals[] = {
        {1000U, "M", 1U}, {900U, "CM", 2U}, {500U, "D", 1U},
        {400U, "CD", 2U}, {100U, "C", 1U},  {90U, "XC", 2U},
        {50U, "L", 1U},   {40U, "XL", 2U},  {10U, "X", 1U},
        {9U, "IX", 2U},   {5U, "V", 1U},    {4U, "IV", 2U},
        {1U, "I", 1U}
    };
    enum { RESULT_SIZE = 16 };
    char *result;
    size_t position = 0U;
    size_t count = sizeof numerals / sizeof numerals[0];

    if (value == 0U || value > 3999U) {
        errno = EDOM;
        return NULL;
    }

    result = malloc(RESULT_SIZE);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0U; i < count; ++i) {
        while (value >= numerals[i].value) {
            if (numerals[i].length > RESULT_SIZE - position - 1U) {
                free(result);
                errno = EOVERFLOW;
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
    enum { INPUT_SIZE = 128 };
    char line[INPUT_SIZE];
    char *end;
    char *roman;
    unsigned long parsed;
    unsigned int value;
    int ch;

    fputs("Enter an integer from 1 to 3999: ", stdout);
    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (fgets(line, sizeof line, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; line[i] != '\0'; ++i) {
        if (line[i] == '\n') {
            line[i] = '\0';
            break;
        }

        if (i == sizeof line - 2U) {
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }

            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    parsed = strtoul(line, &end, 10);

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\v' || *end == '\f') {
        ++end;
    }

    if (end == line || *end != '\0' || errno == ERANGE ||
        parsed > UINT_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    value = (unsigned int)parsed;

    errno = 0;
    roman = integer_to_roman(value);
    if (roman == NULL) {
        if (errno == EDOM) {
            fputs("Value must be from 1 to 3999\n", stderr);
        } else {
            perror("Unable to convert value");
        }
        return EXIT_FAILURE;
    }

    if (printf("%s\n", roman) < 0) {
        free(roman);
        return EXIT_FAILURE;
    }

    free(roman);
    return EXIT_SUCCESS;
}