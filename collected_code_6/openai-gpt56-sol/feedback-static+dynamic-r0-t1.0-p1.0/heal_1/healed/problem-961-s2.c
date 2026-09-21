#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        default: return 0;
    }
}

static int roman_to_int(const char *roman, int *result)
{
    char normalized[16];
    size_t length = 0;
    int total = 0;

    if (roman == NULL || result == NULL) {
        return 0;
    }

    while (length < sizeof(normalized) && roman[length] != '\0') {
        unsigned char c = (unsigned char)roman[length];

        if (c >= 'a' && c <= 'z') {
            c = (unsigned char)(c - 'a' + 'A');
        }

        if (roman_value(c) == 0) {
            return 0;
        }

        normalized[length++] = (char)c;
    }

    if (length == 0 || length == sizeof(normalized)) {
        return 0;
    }

    normalized[length] = '\0';

    for (size_t i = 0; i < length; ++i) {
        int current = roman_value((unsigned char)normalized[i]);
        int next = i + 1 < length
            ? roman_value((unsigned char)normalized[i + 1])
            : 0;

        if (current < next) {
            total -= current;
        } else {
            total += current;
        }
    }

    if (total < 1 || total > 3999) {
        return 0;
    }

    {
        static const struct {
            int value;
            const char *symbol;
        } symbols[] = {
            {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
            {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
            {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
        };
        char canonical[16];
        size_t position = 0;
        int remaining = total;

        for (size_t i = 0; i < sizeof(symbols) / sizeof(symbols[0]); ++i) {
            size_t symbol_length = strlen(symbols[i].symbol);

            while (remaining >= symbols[i].value) {
                if (position + symbol_length >= sizeof(canonical)) {
                    return 0;
                }

                memcpy(canonical + position, symbols[i].symbol, symbol_length);
                position += symbol_length;
                remaining -= symbols[i].value;
            }
        }

        canonical[position] = '\0';

        if (position != length ||
            memcmp(canonical, normalized, length) != 0) {
            return 0;
        }
    }

    *result = total;
    return 1;
}

int main(int argc, char *argv[])
{
    int value;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s ROMAN_NUMERAL\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "roman");
        return EXIT_FAILURE;
    }

    if (!roman_to_int(argv[1], &value)) {
        fputs("Invalid Roman numeral\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%d\n", value);
    return EXIT_SUCCESS;
}