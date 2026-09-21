#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 128U
#define ROMAN_SIZE 16U

static int integer_to_roman(unsigned int value, char *result, size_t size)
{
    static const struct {
        unsigned int value;
        const char *symbol;
    } numerals[] = {
        {1000U, "M"},
        {900U, "CM"},
        {500U, "D"},
        {400U, "CD"},
        {100U, "C"},
        {90U, "XC"},
        {50U, "L"},
        {40U, "XL"},
        {10U, "X"},
        {9U, "IX"},
        {5U, "V"},
        {4U, "IV"},
        {1U, "I"}
    };
    size_t position = 0U;
    size_t i;

    if (value == 0U || value > 3999U || result == NULL || size == 0U) {
        errno = EINVAL;
        return -1;
    }

    for (i = 0U; i < sizeof numerals / sizeof numerals[0]; ++i) {
        while (value >= numerals[i].value) {
            const char *symbol = numerals[i].symbol;

            while (*symbol != '\0') {
                if (position + 1U >= size) {
                    errno = EOVERFLOW;
                    return -1;
                }

                result[position++] = *symbol++;
            }

            value -= numerals[i].value;
        }
    }

    result[position] = '\0';
    return 0;
}

static int read_input(char *buffer, size_t size)
{
    size_t length;
    int ch;

    if (buffer == NULL || size < 2U) {
        return -1;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return -1;
    }

    for (length = 0U; length < size && buffer[length] != '\0'; ++length) {
    }

    if (length == size) {
        return -1;
    }

    if (length > 0U && buffer[length - 1U] == '\n') {
        buffer[length - 1U] = '\0';
        return 0;
    }

    ch = fgetc(stdin);
    if (ch == '\n' || ch == EOF) {
        return 0;
    }

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return -1;
}

int main(void)
{
    char input[INPUT_SIZE];
    char roman[ROMAN_SIZE];
    char *end;
    unsigned long parsed;

    if (read_input(input, sizeof input) != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed = strtoul(input, &end, 10);

    if (end == input || errno == ERANGE || parsed < 1UL || parsed > 3999UL) {
        fputs("Value must be from 1 to 3999\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (integer_to_roman((unsigned int)parsed, roman, sizeof roman) != 0) {
        fputs("Unable to convert value\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", roman) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}