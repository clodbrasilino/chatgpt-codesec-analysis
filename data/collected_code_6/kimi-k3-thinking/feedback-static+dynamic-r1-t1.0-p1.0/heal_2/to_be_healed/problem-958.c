#include <stdio.h>
#include <stdlib.h>

#define MAX_ROMAN_NUMERAL_LENGTH 15
#define MAX_ROMAN_LENGTH (MAX_ROMAN_NUMERAL_LENGTH + 17)

typedef struct {
    int value;
    const char *symbol;
    size_t length;
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
    size_t j;
    size_t pos = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'symbol_len' can be reduced. [variableScope]
     */
    size_t symbol_len;

    if (buffer == NULL || buffer_size == 0) {
        return -1;
    }

    buffer[0] = '\0';

    if (num <= 0 || num > 3999) {
        return -1;
    }

    for (i = 0; i < ROMAN_TABLE_SIZE; i++) {
        symbol_len = roman_table[i].length;
        while (num >= roman_table[i].value) {
            if (symbol_len > (buffer_size - 1) - pos) {
                buffer[0] = '\0';
                return -1;
            }
            for (j = 0; j < symbol_len; j++) {
                buffer[pos] = roman_table[i].symbol[j];
                pos++;
            }
            num -= roman_table[i].value;
        }
    }

    buffer[pos] = '\0';
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

    _Static_assert(sizeof(buffer) > MAX_ROMAN_NUMERAL_LENGTH,
                   "buffer must be larger than the maximum possible numeral");

    for (i = 0; i < num_tests; i++) {
        if (int_to_roman(test_values[i], buffer, sizeof(buffer)) == 0) {
            printf("%d = %s\n", test_values[i], buffer);
        } else {
            printf("%d is out of the supported range (1-3999)\n", test_values[i]);
        }
    }

    return EXIT_SUCCESS;
}