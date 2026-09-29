#include <stdio.h>
#include <stdlib.h>

#define MAX_ROMAN_LENGTH 32

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

    if (num <= 0 || num > 3999) {
        return -1;
    }

    for (i = 0; i < ROMAN_TABLE_SIZE; i++) {
        const size_t symbol_len = roman_table[i].symbol_len;

        while (num >= roman_table[i].value) {
            const size_t remaining = buffer_size - pos;

            if (symbol_len >= remaining) {
                buffer[0] = '\0';
                return -1;
            }

            if (snprintf(buffer + pos, remaining, "%s", roman_table[i].symbol) < 0) {
                buffer[0] = '\0';
                return -1;
            }

            pos += symbol_len;
            num -= roman_table[i].value;
        }
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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