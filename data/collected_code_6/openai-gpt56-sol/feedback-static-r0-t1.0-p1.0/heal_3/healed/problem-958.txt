#include <errno.h>
#include <limits.h>
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
            if (position >= RESULT_SIZE ||
                numerals[i].length >= RESULT_SIZE - position) {
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
    char *line = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    unsigned long parsed;
    unsigned int value;
    char *end;
    char *roman;
    int ch;

    fputs("Enter an integer from 1 to 3999: ", stdout);
    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == SIZE_MAX - 1U) {
            free(line);
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *temporary;

            if (capacity == 0U) {
                new_capacity = 32U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(line);
                    fputs("Invalid input\n", stderr);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2U;
            }

            temporary = realloc(line, new_capacity);
            if (temporary == NULL) {
                free(line);
                perror("Unable to read input");
                return EXIT_FAILURE;
            }

            line = temporary;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(line);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (line == NULL) {
        line = malloc(1U);
        if (line == NULL) {
            perror("Unable to read input");
            return EXIT_FAILURE;
        }
    }

    line[length] = '\0';

    errno = 0;
    parsed = strtoul(line, &end, 10);

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\v' || *end == '\f') {
        ++end;
    }

    if (end == line || *end != '\0' || errno == ERANGE ||
        parsed > UINT_MAX) {
        free(line);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    value = (unsigned int)parsed;
    free(line);

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