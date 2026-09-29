#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROMAN_LENGTH 15U

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
    static const struct {
        int value;
        const char *symbol;
        size_t length;
    } table[] = {
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
    size_t position = 0U;
    size_t i;

    if (buffer == NULL || buffer_size == 0U) {
        return EINVAL;
    }

    buffer[0] = '\0';

    if (value < 1 || value > 3999) {
        return EINVAL;
    }

    for (i = 0U; i < sizeof(table) / sizeof(table[0]); ++i) {
        while (value >= table[i].value) {
            if (table[i].length >= buffer_size - position) {
                buffer[0] = '\0';
                return ERANGE;
            }

            memcpy(buffer + position, table[i].symbol, table[i].length);
            position += table[i].length;
            value -= table[i].value;
        }
    }

    buffer[position] = '\0';
    return 0;
}

static int roman_to_integer(const char *roman, int *result)
{
    size_t length;
    size_t i;
    int total = 0;
    char normalized[MAX_ROMAN_LENGTH + 1U];
    char canonical[MAX_ROMAN_LENGTH + 1U];

    if (roman == NULL || result == NULL) {
        return EINVAL;
    }

    length = strnlen(roman, MAX_ROMAN_LENGTH + 1U);
    if (length == 0U || length > MAX_ROMAN_LENGTH) {
        return EINVAL;
    }

    for (i = 0U; i < length; ++i) {
        unsigned char character = (unsigned char)roman[i];
        char symbol = (char)toupper(character);

        if (roman_value(symbol) == 0) {
            return EINVAL;
        }

        normalized[i] = symbol;
    }
    normalized[length] = '\0';

    for (i = 0U; i < length; ++i) {
        int current = roman_value(normalized[i]);
        int next = i + 1U < length ? roman_value(normalized[i + 1U]) : 0;

        total += current < next ? -current : current;
    }

    if (integer_to_roman(total, canonical, sizeof(canonical)) != 0 ||
        strcmp(normalized, canonical) != 0) {
        return EINVAL;
    }

    *result = total;
    return 0;
}

int main(int argc, char *const argv[])
{
    const char *program_name = "roman";
    int value;

    if (argc > 0 && argv != NULL && argv[0] != NULL) {
        program_name = argv[0];
    }

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s ROMAN_NUMERAL\n", program_name);
        return EXIT_FAILURE;
    }

    if (roman_to_integer(argv[1], &value) != 0) {
        fprintf(stderr, "Invalid Roman numeral\n");
        return EXIT_FAILURE;
    }

    if (printf("%d\n", value) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}