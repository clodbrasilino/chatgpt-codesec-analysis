#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

char *integer_to_roman(unsigned int value)
{
    static const struct {
        unsigned int value;
        char symbol[3];
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
            if (numerals[i].length > (RESULT_SIZE - 1U) - position) {
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
    unsigned int value;
    char extra;
    char *roman;

    printf("Enter an integer from 1 to 3999: ");
    if (scanf("%u%c", &value, &extra) != 2 || extra != '\n') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    roman = integer_to_roman(value);
    if (roman == NULL) {
        if (errno == EDOM) {
            fprintf(stderr, "Value must be from 1 to 3999\n");
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