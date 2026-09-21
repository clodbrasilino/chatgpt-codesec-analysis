#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

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

    enum { RESULT_SIZE = 16 };
    const size_t numeral_count = sizeof numerals / sizeof numerals[0];
    char *result;
    size_t position = 0U;

    if (value == 0U || value > 3999U) {
        errno = EDOM;
        return NULL;
    }

    result = malloc(RESULT_SIZE);
    if (result == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    for (size_t i = 0U; i < numeral_count; ++i) {
        while (value >= numerals[i].value) {
            if (position > (size_t)RESULT_SIZE - 1U ||
                numerals[i].length >
                    (size_t)RESULT_SIZE - 1U - position) {
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

static int discard_line(void)
{
    int ch;

    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    return ch;
}

int main(void)
{
    char input[128];
    char *end;
    char *roman;
    unsigned long parsed;
    size_t length;
    int line_complete;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    length = 0U;
    while (length < sizeof input && input[length] != '\0') {
        ++length;
    }

    line_complete = length > 0U && input[length - 1U] == '\n';

    if (!line_complete && length == sizeof input - 1U) {
        if (discard_line() != '\n') {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed = strtoul(input, &end, 10);

    if (end == input || errno == ERANGE || parsed == 0UL || parsed > 3999UL) {
        fputs("Value must be from 1 to 3999\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && *end != '\n' &&
           isspace((unsigned char)*end) != 0) {
        ++end;
    }

    if (*end != '\0' && *end != '\n') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (*end == '\n') {
        ++end;
        if (*end != '\0') {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    roman = integer_to_roman((unsigned int)parsed);
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