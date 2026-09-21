#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_ROMAN_VALUE 1
#define MAX_ROMAN_VALUE 3999
#define MAX_ROMAN_NUMERAL_LENGTH 15
#define ROMAN_BUFFER_SIZE (MAX_ROMAN_NUMERAL_LENGTH + 1)

typedef struct {
    int value;
    const char *symbol;
    size_t symbol_len;
} RomanEntry;

static const RomanEntry roman_table[] = {
    {1000, "M", sizeof("M") - 1},
    {900, "CM", sizeof("CM") - 1},
    {500, "D", sizeof("D") - 1},
    {400, "CD", sizeof("CD") - 1},
    {100, "C", sizeof("C") - 1},
    {90, "XC", sizeof("XC") - 1},
    {50, "L", sizeof("L") - 1},
    {40, "XL", sizeof("XL") - 1},
    {10, "X", sizeof("X") - 1},
    {9, "IX", sizeof("IX") - 1},
    {5, "V", sizeof("V") - 1},
    {4, "IV", sizeof("IV") - 1},
    {1, "I", sizeof("I") - 1}
};

#define ROMAN_TABLE_SIZE (sizeof(roman_table) / sizeof(roman_table[0]))

_Static_assert(ROMAN_BUFFER_SIZE > MAX_ROMAN_NUMERAL_LENGTH,
               "buffer size must exceed the maximum Roman numeral length");

int int_to_roman(int num, char *buffer, size_t buffer_size)
{
    size_t i;
    size_t pos = 0;

    if (buffer == NULL || buffer_size < ROMAN_BUFFER_SIZE) {
        return -1;
    }

    buffer[0] = '\0';

    if (num < MIN_ROMAN_VALUE || num > MAX_ROMAN_VALUE) {
        return -1;
    }

    for (i = 0; i < ROMAN_TABLE_SIZE; i++) {
        while (num >= roman_table[i].value) {
            size_t remaining = buffer_size - pos;
            int written;

            if (roman_table[i].symbol_len >= remaining) {
                buffer[0] = '\0';
                return -1;
            }

            written = snprintf(buffer + pos, remaining, "%s", roman_table[i].symbol);
            if (written < 0 || (size_t)written != roman_table[i].symbol_len) {
                buffer[0] = '\0';
                return -1;
            }

            pos += (size_t)written;
            num -= roman_table[i].value;
        }
    }

    buffer[pos] = '\0';

    return 0;
}

int main(void)
{
    char *buffer;
    int test_values[] = {1, 4, 9, 14, 40, 58, 444, 1994, 2024, 3999, 0, -5, 4000};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    size_t i;

    buffer = malloc(ROMAN_BUFFER_SIZE);
    if (buffer == NULL) {
        fprintf(stderr, "failed to allocate %d bytes for the Roman numeral buffer\n",
                ROMAN_BUFFER_SIZE);
        return EXIT_FAILURE;
    }

    buffer[0] = '\0';

    for (i = 0; i < num_tests; i++) {
        if (int_to_roman(test_values[i], buffer, ROMAN_BUFFER_SIZE) == 0) {
            printf("%d = %s\n", test_values[i], buffer);
        } else {
            printf("%d is out of the supported range (%d-%d)\n",
                   test_values[i], MIN_ROMAN_VALUE, MAX_ROMAN_VALUE);
        }
    }

    free(buffer);
    buffer = NULL;

    return EXIT_SUCCESS;
}