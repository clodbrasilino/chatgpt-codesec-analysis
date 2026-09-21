#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROMAN_BUFFER_SIZE 32
#define ROMAN_TABLE_SIZE 13
#define ROMAN_SYMBOL_MAX 3

static const int roman_values[ROMAN_TABLE_SIZE] = {
    1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1
};

static const char roman_symbols[ROMAN_TABLE_SIZE][ROMAN_SYMBOL_MAX] = {
    "M", "CM", "D", "CD", "C", "XC", "L", "XL",
    "X", "IX", "V", "IV", "I"
};

static const size_t roman_symbol_lengths[ROMAN_TABLE_SIZE] = {
    1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1
};

int int_to_roman(int number, char *buffer, size_t buffer_size)
{
    size_t used = 0;
    size_t i;

    if (buffer == NULL || buffer_size == 0) {
        return -1;
    }

    buffer[0] = '\0';

    if (number < 1 || number > 3999) {
        return -1;
    }

    for (i = 0; i < ROMAN_TABLE_SIZE; i++) {
        size_t sym_len = roman_symbol_lengths[i];

        if (sym_len >= ROMAN_SYMBOL_MAX) {
            buffer[0] = '\0';
            return -1;
        }

        while (number >= roman_values[i]) {
            if (used >= buffer_size || sym_len >= buffer_size - used) {
                buffer[0] = '\0';
                return -1;
            }
            memcpy(buffer + used, roman_symbols[i], sym_len);
            used += sym_len;
            number -= roman_values[i];
        }
    }

    if (used >= buffer_size) {
        buffer[0] = '\0';
        return -1;
    }

    buffer[used] = '\0';
    return 0;
}

int main(void)
{
    char roman[ROMAN_BUFFER_SIZE];
    int test_values[] = { 1, 4, 9, 14, 40, 90, 400, 1994, 2024, 3999 };
    size_t count = sizeof(test_values) / sizeof(test_values[0]);
    size_t i;

    memset(roman, 0, sizeof(roman));

    for (i = 0; i < count; i++) {
        if (int_to_roman(test_values[i], roman, sizeof(roman)) == 0) {
            if (printf("%d -> %s\n", test_values[i], roman) < 0) {
                return EXIT_FAILURE;
            }
        } else {
            if (fprintf(stderr, "Conversion failed for %d\n",
                        test_values[i]) < 0) {
                return EXIT_FAILURE;
            }
        }
    }

    if (int_to_roman(0, roman, sizeof(roman)) != 0) {
        if (printf("0 is out of range, as expected\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    if (int_to_roman(4000, roman, sizeof(roman)) != 0) {
        if (printf("4000 is out of range, as expected\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}