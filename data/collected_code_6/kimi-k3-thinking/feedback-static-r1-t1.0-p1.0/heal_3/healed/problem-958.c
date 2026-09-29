#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROMAN_LENGTH 32
#define MIN_ROMAN_VALUE 1
#define MAX_ROMAN_VALUE 3999

typedef struct {
    int value;
    const char *symbol;
    size_t symbol_len;
} RomanEntry;

static const RomanEntry roman_table[] = {
    {1000, "M", 1},
    {900, "CM", 2},
    {500, "D", 1},
    {400, "CD", 2},
    {100, "C", 1},
    {90, "XC", 2},
    {50, "L", 1},
    {40, "XL", 2},
    {10, "X", 1},
    {9, "IX", 2},
    {5, "V", 1},
    {4, "IV", 2},
    {1, "I", 1}
};

#define ROMAN_TABLE_SIZE (sizeof(roman_table) / sizeof(roman_table[0]))

int int_to_roman(int num, char *buffer, size_t buffer_size)
{
    size_t i;
    size_t pos = 0;

    if (buffer == NULL || buffer_size == 0) {
        return -1;
    }

    buffer[0] = '\0';

    if (num < MIN_ROMAN_VALUE || num > MAX_ROMAN_VALUE) {
        return -1;
    }

    for (i = 0; i < ROMAN_TABLE_SIZE; i++) {
        const size_t symbol_len = roman_table[i].symbol_len;

        while (num >= roman_table[i].value) {
            if (symbol_len >= buffer_size - pos) {
                buffer[0] = '\0';
                return -1;
            }

            memcpy(buffer + pos, roman_table[i].symbol, symbol_len);
            pos += symbol_len;
            buffer[pos] = '\0';

            num -= roman_table[i].value;
        }
    }

    return 0;
}

int main(void)
{
    char buffer[MAX_ROMAN_LENGTH];
    int test_values[] = {1, 4, 9, 14, 40, 58, 444, 1994, 2024, 3999, 0, -5, 4000};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    size_t i;

    if (sizeof(buffer) < 10) {
        fprintf(stderr, "buffer size is smaller than the maximum possible Roman numeral length\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < num_tests; i++) {
        if (int_to_roman(test_values[i], buffer, sizeof(buffer)) == 0) {
            printf("%d = %s\n", test_values[i], buffer);
        } else {
            printf("%d is out of the supported range (%d-%d)\n",
                   test_values[i], MIN_ROMAN_VALUE, MAX_ROMAN_VALUE);
        }
    }

    return EXIT_SUCCESS;
}