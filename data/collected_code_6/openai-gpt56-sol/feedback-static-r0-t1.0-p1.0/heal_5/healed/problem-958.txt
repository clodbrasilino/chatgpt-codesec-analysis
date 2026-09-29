#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

char *integer_to_roman(unsigned int value)
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
    enum { RESULT_SIZE = 16 };
    char *result;
    size_t position = 0U;

    if (value == 0U || value > 3999U) {
        errno = EDOM;
        return NULL;
    }

    result = malloc(RESULT_SIZE);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0U; i < sizeof numerals / sizeof numerals[0]; ++i) {
        while (value >= numerals[i].value) {
            const char *symbol = numerals[i].symbol;

            while (*symbol != '\0') {
                if (position >= RESULT_SIZE - 1U) {
                    free(result);
                    errno = EOVERFLOW;
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
    char *line = NULL;
    size_t capacity = 0U;
    ssize_t length;
    char *end;
    char *roman;
    unsigned long parsed;

    fputs("Enter an integer from 1 to 3999: ", stdout);
    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > 0 && line[length - 1] == '\n') {
        line[--length] = '\0';
    }

    if (length > 0 && line[length - 1] == '\r') {
        line[--length] = '\0';
    }

    errno = 0;
    parsed = strtoul(line, &end, 10);

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\v' || *end == '\f') {
        ++end;
    }

    if (end == line || *end != '\0' || errno == ERANGE ||
        parsed == 0UL || parsed > 3999UL) {
        free(line);
        fputs("Value must be from 1 to 3999\n", stderr);
        return EXIT_FAILURE;
    }

    free(line);

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