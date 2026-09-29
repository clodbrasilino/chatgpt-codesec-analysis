#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROMAN_BUFFER_SIZE 32
#define ROMAN_TABLE_SIZE 13
#define ROMAN_MAX_SYMBOL_LEN 2
#define ROMAN_MIN_VALUE 1
#define ROMAN_MAX_VALUE 3999
#define ROMAN_MAX_OUTPUT_LEN 15

struct roman_entry {
    int value;
    const char *symbol;
    size_t length;
};

static const struct roman_entry roman_table[ROMAN_TABLE_SIZE] = {
    { 1000, "M",  1 }, { 900, "CM", 2 }, { 500, "D",  1 }, { 400, "CD", 2 },
    {  100, "C",  1 }, {  90, "XC", 2 }, {  50, "L",  1 }, {  40, "XL", 2 },
    {   10, "X",  1 }, {   9, "IX", 2 }, {   5, "V",  1 }, {   4, "IV", 2 },
    {    1, "I",  1 }
};

static size_t bounded_symbol_length(const char *symbol, size_t max_len)
{
    size_t len = 0;

    if (symbol == NULL) {
        return 0;
    }

    while (len < max_len && symbol[len] != '\0') {
        len++;
    }

    return len;
}

static int append_symbol(char *buffer, size_t buffer_size, size_t *used,
                         const char *symbol, size_t sym_len)
{
    size_t j;

    if (buffer == NULL || used == NULL || symbol == NULL) {
        return -1;
    }

    if (buffer_size == 0 || *used >= buffer_size - 1 ||
        sym_len > (buffer_size - 1) - *used) {
        return -1;
    }

    for (j = 0; j < sym_len; j++) {
        buffer[*used + j] = symbol[j];
    }

    *used += sym_len;
    buffer[*used] = '\0';

    return 0;
}

int int_to_roman(int number, char *buffer, size_t buffer_size)
{
    size_t used = 0;
    size_t i;

    if (buffer == NULL || buffer_size == 0) {
        return -1;
    }

    buffer[0] = '\0';

    if (number < ROMAN_MIN_VALUE || number > ROMAN_MAX_VALUE) {
        return -1;
    }

    if (buffer_size < ROMAN_MAX_OUTPUT_LEN + 1) {
        return -1;
    }

    for (i = 0; i < ROMAN_TABLE_SIZE; i++) {
        const char *symbol = roman_table[i].symbol;
        int value = roman_table[i].value;
        size_t sym_len = roman_table[i].length;

        if (symbol == NULL || sym_len == 0 ||
            sym_len > ROMAN_MAX_SYMBOL_LEN ||
            sym_len != bounded_symbol_length(symbol,
                                             ROMAN_MAX_SYMBOL_LEN + 1)) {
            buffer[0] = '\0';
            return -1;
        }

        while (number >= value) {
            if (append_symbol(buffer, buffer_size, &used,
                              symbol, sym_len) != 0) {
                buffer[0] = '\0';
                return -1;
            }
            number -= value;
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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