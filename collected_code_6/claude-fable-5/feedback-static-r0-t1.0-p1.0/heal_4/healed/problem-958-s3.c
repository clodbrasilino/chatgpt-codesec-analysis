#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROMAN_BUFFER_SIZE 32
#define ROMAN_MIN 1
#define ROMAN_MAX 3999

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
    size_t used = 0;
    size_t i;

    if (buffer == NULL || buffer_size == 0) {
        return -1;
    }

    buffer[0] = '\0';

    if (number < ROMAN_MIN || number > ROMAN_MAX) {
        return -1;
    }

    for (i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        while (number >= values[i]) {
            size_t sym_len = strnlen(symbols[i], sizeof(symbols[i]));
            size_t j;

            if (used >= buffer_size || sym_len >= buffer_size - used) {
                buffer[0] = '\0';
                return -1;
            }

            for (j = 0; j < sym_len && (used + j) < buffer_size - 1; j++) {
                buffer[used + j] = symbols[i][j];
            }

            if (j < sym_len) {
                buffer[0] = '\0';
                return -1;
            }

            used += sym_len;
            buffer[used] = '\0';
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