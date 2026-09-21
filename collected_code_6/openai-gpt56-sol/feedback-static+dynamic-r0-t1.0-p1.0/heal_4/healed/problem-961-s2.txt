#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROMAN_MAX_LENGTH 15U

struct RomanSymbol {
    int value;
    const char *symbol;
    size_t length;
};

static int roman_value(unsigned char c)
{
    switch (c) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default:  return 0;
    }
}

static int roman_to_int(const char *roman, int *result)
{
    static const struct RomanSymbol symbols[] = {
        {1000, "M",  1U},
        { 900, "CM", 2U},
        { 500, "D",  1U},
        { 400, "CD", 2U},
        { 100, "C",  1U},
        {  90, "XC", 2U},
        {  50, "L",  1U},
        {  40, "XL", 2U},
        {  10, "X",  1U},
        {   9, "IX", 2U},
        {   5, "V",  1U},
        {   4, "IV", 2U},
        {   1, "I",  1U}
    };

    char normalized[ROMAN_MAX_LENGTH + 1U];
    char canonical[ROMAN_MAX_LENGTH + 1U];
    size_t length;
    size_t position = 0U;
    int total = 0;
    int remaining;

    if (roman == NULL || result == NULL) {
        return 0;
    }

    length = strnlen(roman, ROMAN_MAX_LENGTH + 1U);
    if (length == 0U || length > ROMAN_MAX_LENGTH) {
        return 0;
    }

    for (size_t i = 0U; i < length; ++i) {
        unsigned char c = (unsigned char)roman[i];

        if (c >= (unsigned char)'a' && c <= (unsigned char)'z') {
            c = (unsigned char)(c - (unsigned char)'a' + (unsigned char)'A');
        }

        if (roman_value(c) == 0) {
            return 0;
        }

        normalized[i] = (char)c;
    }
    normalized[length] = '\0';

    for (size_t i = 0U; i < length; ++i) {
        int current = roman_value((unsigned char)normalized[i]);
        int next = i + 1U < length
            ? roman_value((unsigned char)normalized[i + 1U])
            : 0;

        total += current < next ? -current : current;
    }

    if (total < 1 || total > 3999) {
        return 0;
    }

    remaining = total;

    for (size_t i = 0U; i < sizeof(symbols) / sizeof(symbols[0]); ++i) {
        while (remaining >= symbols[i].value) {
            size_t available = sizeof(canonical) - position;

            if (symbols[i].length >= available) {
                return 0;
            }

            memcpy(canonical + position, symbols[i].symbol, symbols[i].length);
            position += symbols[i].length;
            remaining -= symbols[i].value;
        }
    }

    canonical[position] = '\0';

    if (remaining != 0 || position != length ||
        memcmp(canonical, normalized, length) != 0) {
        return 0;
    }

    *result = total;
    return 1;
}

int main(int argc, char *const argv[])
{
    int value;

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        const char *program = "roman";

        if (argc > 0 && argv != NULL && argv[0] != NULL) {
            program = argv[0];
        }

        fprintf(stderr, "Usage: %s ROMAN_NUMERAL\n", program);
        return EXIT_FAILURE;
    }

    if (!roman_to_int(argv[1], &value)) {
        fputs("Invalid Roman numeral\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%d\n", value) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}