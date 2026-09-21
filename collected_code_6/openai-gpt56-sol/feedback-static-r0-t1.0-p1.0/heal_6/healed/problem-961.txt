#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROMAN_LENGTH 15U

struct roman_entry {
    int value;
    const char *symbols;
    size_t length;
};

static const struct roman_entry roman_table[] = {
    {1000, "M", 1U},
    {900, "CM", 2U},
    {500, "D", 1U},
    {400, "CD", 2U},
    {100, "C", 1U},
    {90, "XC", 2U},
    {50, "L", 1U},
    {40, "XL", 2U},
    {10, "X", 1U},
    {9, "IX", 2U},
    {5, "V", 1U},
    {4, "IV", 2U},
    {1, "I", 1U}
};

static int roman_value(char symbol)
{
    switch (symbol) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return 0;
    }
}

static int integer_to_roman(int value, char *buffer, size_t buffer_size)
{
    size_t position = 0U;
    size_t i;

    if (buffer == NULL || buffer_size == 0U) {
        return EINVAL;
    }

    buffer[0] = '\0';

    if (value < 1 || value > 3999) {
        return EINVAL;
    }

    for (i = 0U; i < sizeof roman_table / sizeof roman_table[0]; ++i) {
        while (value >= roman_table[i].value) {
            size_t length = roman_table[i].length;

            if (position >= buffer_size ||
                length >= buffer_size - position) {
                buffer[0] = '\0';
                return ERANGE;
            }

            memcpy(buffer + position, roman_table[i].symbols, length);
            position += length;
            value -= roman_table[i].value;
        }
    }

    buffer[position] = '\0';
    return 0;
}

static int roman_to_integer(const char *roman, int *result)
{
    char *normalized = NULL;
    char *canonical = NULL;
    size_t length;
    size_t i;
    int total = 0;
    int status = EINVAL;

    if (roman == NULL || result == NULL) {
        return EINVAL;
    }

    *result = 0;

    length = strnlen(roman, MAX_ROMAN_LENGTH + 1U);
    if (length == 0U || length > MAX_ROMAN_LENGTH) {
        return EINVAL;
    }

    if (length == SIZE_MAX) {
        return ERANGE;
    }

    normalized = malloc(length + 1U);
    canonical = malloc(length + 1U);
    if (normalized == NULL || canonical == NULL) {
        status = ENOMEM;
        goto cleanup;
    }

    for (i = 0U; i < length; ++i) {
        unsigned char character = (unsigned char)roman[i];
        char symbol = (char)toupper(character);

        if (roman_value(symbol) == 0) {
            goto cleanup;
        }

        normalized[i] = symbol;
    }
    normalized[length] = '\0';

    for (i = 0U; i < length; ++i) {
        int current = roman_value(normalized[i]);
        int next = i + 1U < length
                       ? roman_value(normalized[i + 1U])
                       : 0;

        if (current < next) {
            total -= current;
        } else {
            total += current;
        }
    }

    status = integer_to_roman(total, canonical, length + 1U);
    if (status != 0 || strcmp(normalized, canonical) != 0) {
        status = EINVAL;
        goto cleanup;
    }

    *result = total;
    status = 0;

cleanup:
    free(canonical);
    free(normalized);
    return status;
}

int main(int argc, char *argv[])
{
    const char *program_name;
    int value;
    int status;

    program_name = argc > 0 && argv != NULL && argv[0] != NULL
                       ? argv[0]
                       : "roman";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s ROMAN_NUMERAL\n", program_name);
        return EXIT_FAILURE;
    }

    status = roman_to_integer(argv[1], &value);
    if (status != 0) {
        fputs("Invalid Roman numeral\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%d\n", value) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}