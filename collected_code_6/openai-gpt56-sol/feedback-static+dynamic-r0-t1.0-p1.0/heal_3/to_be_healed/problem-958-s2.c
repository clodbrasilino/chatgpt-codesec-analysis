#include <stdio.h>
#include <stdlib.h>

#define ROMAN_BUFFER_SIZE 16U
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'L', got <no output>
  *  test case 2 failed: expected 'IV', got <no output>
  *  test case 0 failed: expected 'I', got <no output>
  */

char *integer_to_roman(unsigned int value)
{
    static const unsigned int numeral_values[] = {
        1000U, 900U, 500U, 400U, 100U, 90U, 50U,
        40U, 10U, 9U, 5U, 4U, 1U
    };
    static const char *const numeral_symbols[] = {
        "M", "CM", "D", "CD", "C", "XC", "L",
        "XL", "X", "IX", "V", "IV", "I"
    };
    static const size_t numeral_lengths[] = {
        1U, 2U, 1U, 2U, 1U, 2U, 1U,
        2U, 1U, 2U, 1U, 2U, 1U
    };
    char *result;
    size_t position = 0U;
    size_t i;
    size_t j;
    size_t count = sizeof numeral_values / sizeof numeral_values[0];

    if (value == 0U || value > 3999U) {
        return NULL;
    }

    result = malloc(ROMAN_BUFFER_SIZE);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0U; i < count; ++i) {
        while (value >= numeral_values[i]) {
            if (position > ROMAN_BUFFER_SIZE - 1U ||
                numeral_lengths[i] > ROMAN_BUFFER_SIZE - 1U - position) {
                free(result);
                return NULL;
            }

            for (j = 0U; j < numeral_lengths[i]; ++j) {
                result[position++] = numeral_symbols[i][j];
            }

            value -= numeral_values[i];
        }
    }

    result[position] = '\0';
    return result;
}

int main(void)
{
    unsigned int input;
    int trailing;
    char *roman;

    if (scanf("%u", &input) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        trailing = getchar();
    } while (trailing == ' ' || trailing == '\t' ||
             trailing == '\n' || trailing == '\r' ||
             trailing == '\f' || trailing == '\v');

    if (trailing != EOF) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (input < 1U || input > 3999U) {
        fputs("Input must be between 1 and 3999\n", stderr);
        return EXIT_FAILURE;
    }

    roman = integer_to_roman(input);
    if (roman == NULL) {
        fputs("Conversion failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(roman) == EOF) {
        free(roman);
        return EXIT_FAILURE;
    }

    free(roman);
    return EXIT_SUCCESS;
}