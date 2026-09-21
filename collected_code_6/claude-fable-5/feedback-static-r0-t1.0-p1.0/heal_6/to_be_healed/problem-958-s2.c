#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROMAN_BUFFER_SIZE 32
#define ROMAN_MIN 1
#define ROMAN_MAX 3999

typedef struct {
    int value;
    const char *symbol;
    size_t length;
} roman_entry;

int int_to_roman(int number, char *output, size_t output_size)
{
    static const roman_entry table[] = {
        { 1000, "M",  1 },
        {  900, "CM", 2 },
        {  500, "D",  1 },
        {  400, "CD", 2 },
        {  100, "C",  1 },
        {   90, "XC", 2 },
        {   50, "L",  1 },
        {   40, "XL", 2 },
        {   10, "X",  1 },
        {    9, "IX", 2 },
        {    5, "V",  1 },
        {    4, "IV", 2 },
        {    1, "I",  1 }
    };
    size_t used = 0;
    size_t i;

    if (output == NULL || output_size == 0) {
        return -1;
    }

    output[0] = '\0';

    if (number < ROMAN_MIN || number > ROMAN_MAX) {
        return -1;
    }

    for (i = 0; i < sizeof(table) / sizeof(table[0]); i++) {
        while (number >= table[i].value) {
            size_t symbol_len = table[i].length;

            if (output_size <= symbol_len ||
                used > output_size - symbol_len - 1) {
                output[0] = '\0';
                return -1;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(output + used, table[i].symbol, symbol_len);
            used += symbol_len;
            output[used] = '\0';
            number -= table[i].value;
        }
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[ROMAN_BUFFER_SIZE];
    int test_values[] = { 1, 4, 9, 14, 40, 90, 400, 1994, 2024, 3999 };
    size_t count = sizeof(test_values) / sizeof(test_values[0]);
    size_t i;

    memset(buffer, 0, sizeof(buffer));

    for (i = 0; i < count; i++) {
        if (int_to_roman(test_values[i], buffer, sizeof(buffer)) == 0) {
            if (printf("%d -> %s\n", test_values[i], buffer) < 0) {
                return EXIT_FAILURE;
            }
        } else {
            if (fprintf(stderr, "Conversion failed for %d\n",
                        test_values[i]) < 0) {
                return EXIT_FAILURE;
            }
        }
    }

    if (int_to_roman(0, buffer, sizeof(buffer)) != 0) {
        if (printf("Correctly rejected out-of-range value 0\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    if (int_to_roman(4000, buffer, sizeof(buffer)) != 0) {
        if (printf("Correctly rejected out-of-range value 4000\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}