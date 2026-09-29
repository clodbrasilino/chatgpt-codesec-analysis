#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROMAN_BUFFER_SIZE 32

int int_to_roman(int number, char *buffer, size_t buffer_size);

int int_to_roman(int number, char *buffer, size_t buffer_size)
{
    static const int values[] = {
        1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1
    };
    static const char symbols[][3] = {
        "M", "CM", "D", "CD", "C", "XC", "L", "XL",
        "X", "IX", "V", "IV", "I"
    };
    static const size_t symbol_lengths[] = {
        1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1
    };
    size_t used = 0;
    size_t i;

    if (buffer == NULL || buffer_size == 0) {
        return -1;
    }

    buffer[0] = '\0';

    if (number < 1 || number > 3999) {
        return -1;
    }

    for (i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        while (number >= values[i]) {
            size_t sym_len = symbol_lengths[i];

            if (used >= buffer_size || sym_len >= buffer_size - used) {
                buffer[0] = '\0';
                return -1;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(buffer + used, symbols[i], sym_len);
            used += sym_len;
            number -= values[i];
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