#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define ROMAN_BUFFER_SIZE 16U

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
    char *result;
    size_t position = 0U;
    size_t i;

    if (value < 1U || value > 3999U) {
        return NULL;
    }

    result = malloc(ROMAN_BUFFER_SIZE);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0U; i < sizeof numeral_values / sizeof numeral_values[0]; ++i) {
        while (value >= numeral_values[i]) {
            const char *symbol = numeral_symbols[i];

            while (*symbol != '\0') {
                if (position + 1U >= ROMAN_BUFFER_SIZE) {
                    free(result);
                    return NULL;
                }

                result[position++] = *symbol++;
            }

            value -= numeral_values[i];
        }
    }

    result[position] = '\0';
    return result;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[128];
    char *end;
    char *roman;
    unsigned long value;

    if (fgets(input_buffer, sizeof input_buffer, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = input_buffer;
    value = strtoul(input_buffer, &end, 10);

    if (end == input_buffer || errno == ERANGE || value > UINT_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (value < 1UL || value > 3999UL) {
        fputs("Input must be between 1 and 3999\n", stderr);
        return EXIT_FAILURE;
    }

    roman = integer_to_roman((unsigned int)value);
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