#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROMAN_BUFFER_SIZE 32
#define ROMAN_TABLE_SIZE 13

struct roman_entry {
    int value;
    const char *symbol;
};

static const struct roman_entry roman_table[ROMAN_TABLE_SIZE] = {
    { 1000, "M"  }, { 900, "CM" }, { 500, "D"  }, { 400, "CD" },
    {  100, "C"  }, {  90, "XC" }, {  50, "L"  }, {  40, "XL" },
    {   10, "X"  }, {   9, "IX" }, {   5, "V"  }, {   4, "IV" },
    {    1, "I"  }
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
        const char *symbol = roman_table[i].symbol;
        int value = roman_table[i].value;
        size_t sym_len = strlen(symbol);

        while (number >= value) {
            size_t j;

            if (used >= buffer_size - 1 ||
                sym_len > (buffer_size - 1) - used) {
                buffer[0] = '\0';
                return -1;
            }

            for (j = 0; j < sym_len; j++) {
                buffer[used + j] = symbol[j];
            }

            used += sym_len;
            buffer[used] = '\0';
            number -= value;
        }
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