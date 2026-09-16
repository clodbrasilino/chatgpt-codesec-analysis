#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    } table[] = {
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
        {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
        {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
    };

    size_t position = 0U;

    if (value < 1 || value > 3999 || buffer == NULL || buffer_size == 0U) {
        return EINVAL;
    }

    for (size_t i = 0U; i < sizeof(table) / sizeof(table[0]); ++i) {
        const size_t symbol_length = strlen(table[i].symbol);

        while (value >= table[i].value) {
            if (position >= buffer_size ||
                symbol_length >= buffer_size - position) {
                buffer[0] = '\0';
                return ERANGE;
            }

            memcpy(buffer + position, table[i].symbol, symbol_length);
            position += symbol_length;
            value -= table[i].value;
        }
    }

    buffer[position] = '\0';
    return 0;
}

static int roman_to_integer(const char *roman, int *result)
{
    char normalized[16];
    char canonical[16];
    size_t length;
    int total = 0;

    if (roman == NULL || result == NULL) {
        return EINVAL;
    }

    length = strlen(roman);
    if (length == 0U || length >= sizeof(normalized)) {
        return EINVAL;
    }

    for (size_t i = 0U; i < length; ++i) {
        const unsigned char character = (unsigned char)roman[i];
        const char symbol = (char)toupper(character);

        if (roman_value(symbol) == 0) {
            return EINVAL;
        }

        normalized[i] = symbol;
    }
    normalized[length] = '\0';

    for (size_t i = 0U; i < length; ++i) {
        const int current = roman_value(normalized[i]);
        const int next =
            i + 1U < length ? roman_value(normalized[i + 1U]) : 0;

        if (current < next) {
            if (total < INT_MIN + current) {
                return ERANGE;
            }
            total -= current;
        } else {
            if (total > INT_MAX - current) {
                return ERANGE;
            }
            total += current;
        }
    }

    if (integer_to_roman(total, canonical, sizeof(canonical)) != 0 ||
        strcmp(normalized, canonical) != 0) {
        return EINVAL;
    }

    *result = total;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    int value;
    int status;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s ROMAN_NUMERAL\n", argv[0]);
        return EXIT_FAILURE;
    }

    status = roman_to_integer(argv[1], &value);
    if (status != 0) {
        fprintf(stderr, "Invalid Roman numeral: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    if (printf("%d\n", value) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}