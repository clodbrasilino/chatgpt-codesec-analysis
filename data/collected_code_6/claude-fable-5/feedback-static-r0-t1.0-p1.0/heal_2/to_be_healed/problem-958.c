#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROMAN_BUFFER_SIZE 16
#define MIN_ROMAN_VALUE 1
#define MAX_ROMAN_VALUE 3999

int int_to_roman(int number, char *buffer, size_t buffer_size)
{
    static const int values[] = {
        1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1
    };
    static const char symbols[][3] = {
        "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"
    };
    static const size_t symbol_lengths[] = {
        1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1
    };
    size_t used = 0;
    size_t i;

    if (buffer == NULL || buffer_size == 0) {
        return -1;
    }

    if (number < MIN_ROMAN_VALUE || number > MAX_ROMAN_VALUE) {
        return -1;
    }

    buffer[0] = '\0';

    for (i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        while (number >= values[i]) {
            size_t sym_len = symbol_lengths[i];

            if (sym_len >= buffer_size || used > buffer_size - sym_len - 1) {
                buffer[0] = '\0';
                return -1;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(buffer + used, symbols[i], sym_len);
            used += sym_len;
            buffer[used] = '\0';
            number -= values[i];
        }
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char roman[ROMAN_BUFFER_SIZE] = { 0 };
    int test_values[] = { 1, 4, 9, 14, 40, 90, 400, 1994, 2024, 3999 };
    size_t i;
    int input;

    for (i = 0; i < sizeof(test_values) / sizeof(test_values[0]); i++) {
        if (int_to_roman(test_values[i], roman, sizeof(roman)) == 0) {
            printf("%d -> %s\n", test_values[i], roman);
        } else {
            fprintf(stderr, "Conversion failed for %d\n", test_values[i]);
            return EXIT_FAILURE;
        }
    }

    printf("Enter an integer (1-3999): ");
    if (scanf("%d", &input) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (int_to_roman(input, roman, sizeof(roman)) != 0) {
        fprintf(stderr, "Value out of range (1-3999)\n");
        return EXIT_FAILURE;
    }

    printf("%d -> %s\n", input, roman);

    return EXIT_SUCCESS;
}