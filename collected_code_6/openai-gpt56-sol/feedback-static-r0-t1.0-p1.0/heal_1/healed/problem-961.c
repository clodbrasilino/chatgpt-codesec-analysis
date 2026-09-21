#include <ctype.h>
#include <errno.h>
#include <limits.h>
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
        char first;
        char second;
        size_t length;
    } table[] = {
        {1000, 'M', '\0', 1U},
        {900,  'C', 'M',  2U},
        {500,  'D', '\0', 1U},
        {400,  'C', 'D',  2U},
        {100,  'C', '\0', 1U},
        {90,   'X', 'C',  2U},
        {50,   'L', '\0', 1U},
        {40,   'X', 'L',  2U},
        {10,   'X', '\0', 1U},
        {9,    'I', 'X',  2U},
        {5,    'V', '\0', 1U},
        {4,    'I', 'V',  2U},
        {1,    'I', '\0', 1U}
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
            if (position >= buffer_size ||
                table[i].length >= buffer_size - position) {
                buffer[0] = '\0';
                return ERANGE;
            }

            buffer[position++] = table[i].first;
            if (table[i].length == 2U) {
                buffer[position++] = table[i].second;
            }

            value -= table[i].value;
        }
    }

    buffer[position] = '\0';
    return 0;
}

static int roman_to_integer(const char *roman, int *result)
{
    char normalized[MAX_ROMAN_LENGTH + 1U];
    char canonical[MAX_ROMAN_LENGTH + 1U];
    size_t length = 0U;
    size_t i;
    int total = 0;

    if (roman == NULL || result == NULL) {
        return EINVAL;
    }

    while (length <= MAX_ROMAN_LENGTH && roman[length] != '\0') {
        ++length;
    }

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

int main(int argc, char *argv[])
{
    int value;
    int status;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s ROMAN_NUMERAL\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "roman");
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