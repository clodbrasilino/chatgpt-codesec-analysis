#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 128U
#define ROMAN_SIZE 16U

static int integer_to_roman(unsigned int value, char *buffer, size_t size)
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
    size_t position = 0U;
    size_t i;

    if (buffer == NULL || size == 0U) {
        return 0;
    }

    buffer[0] = '\0';

    if (value == 0U || value > 3999U) {
        return 0;
    }

    for (i = 0U; i < sizeof numerals / sizeof numerals[0]; ++i) {
        while (value >= numerals[i].value) {
            const char *symbol = numerals[i].symbol;

            while (*symbol != '\0') {
                if (position >= size - 1U) {
                    buffer[0] = '\0';
                    return 0;
                }

                buffer[position++] = *symbol++;
            }

            value -= numerals[i].value;
        }
    }

    buffer[position] = '\0';
    return 1;
}

static int read_line(FILE *stream, char *buffer, size_t size)
{
    size_t position = 0U;
    int ch;

    if (stream == NULL || buffer == NULL || size < 2U) {
        return 0;
    }

    buffer[0] = '\0';

    while ((ch = fgetc(stream)) != '\n' && ch != EOF) {
        if (position >= size - 1U) {
            while ((ch = fgetc(stream)) != '\n' && ch != EOF) {
            }

            buffer[0] = '\0';

            if (ch == EOF && ferror(stream)) {
                return 0;
            }

            return 0;
        }

        buffer[position++] = (char)ch;
    }

    if (ch == EOF && ferror(stream)) {
        buffer[0] = '\0';
        return 0;
    }

    buffer[position] = '\0';
    return position != 0U;
}

int main(void)
{
    char input[INPUT_SIZE];
    char roman[ROMAN_SIZE];
    char *end;
    unsigned long parsed;

    if (!read_line(stdin, input, sizeof input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
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

    if (!integer_to_roman((unsigned int)parsed, roman, sizeof roman)) {
        fputs("Value must be between 1 and 3999\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", roman) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}