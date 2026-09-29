#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROMAN_LENGTH 16

typedef struct {
    int value;
    const char *symbol;
} RomanEntry;

static const RomanEntry roman_table[] = {
    {1000, "M"},
    {900, "CM"},
    {500, "D"},
    {400, "CD"},
    {100, "C"},
    {90, "XC"},
    {50, "L"},
    {40, "XL"},
    {10, "X"},
    {9, "IX"},
    {5, "V"},
    {4, "IV"},
    {1, "I"}
};

#define ROMAN_TABLE_SIZE (sizeof(roman_table) / sizeof(roman_table[0]))

int int_to_roman(int num, char *buffer, size_t buffer_size)
{
    size_t i;
    size_t pos = 0;
    size_t symbol_len;

    if (buffer == NULL || buffer_size == 0) {
        return -1;
    }

    buffer[0] = '\0';

    if (num <= 0 || num > 3999) {
        return -1;
    }

    for (i = 0; i < ROMAN_TABLE_SIZE; i++) {
        while (num >= roman_table[i].value) {
            symbol_len = strlen(roman_table[i].symbol);
            if (pos + symbol_len >= buffer_size) {
                buffer[0] = '\0';
                return -1;
            }
            memcpy(buffer + pos, roman_table[i].symbol, symbol_len);
            pos += symbol_len;
            num -= roman_table[i].value;
        }
    }

    buffer[pos] = '\0';
    return 0;
}

int main(void)
{
    char buffer[MAX_ROMAN_LENGTH];
    int test_values[] = {1, 4, 9, 14, 40, 58, 444, 1994, 2024, 3999, 0, -5, 4000};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    size_t i;

    for (i = 0; i < num_tests; i++) {
        if (int_to_roman(test_values[i], buffer, sizeof(buffer)) == 0) {
            printf("%d = %s\n", test_values[i], buffer);
        } else {
            printf("%d is out of the supported range (1-3999)\n", test_values[i]);
        }
    }

    return EXIT_SUCCESS;
}