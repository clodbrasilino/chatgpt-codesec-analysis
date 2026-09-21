#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_BUFFER_SIZE 128U
#define ROMAN_BUFFER_SIZE 16U

static int read_input(char *buffer, size_t size)
{
    size_t length;
    int ch;

    if (buffer == NULL || size < 2U || size > (size_t)INT_MAX) {
        return 0;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return 0;
    }

    for (length = 0U; length < size && buffer[length] != '\0'; ++length) {
    }

    if (length == size) {
        buffer[0] = '\0';
        return 0;
    }

    if (length > 0U && buffer[length - 1U] == '\n') {
        buffer[length - 1U] = '\0';
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    ch = getchar();
    if (ch == EOF) {
        return 1;
    }

    while (ch != '\n' && ch != EOF) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    }

    buffer[0] = '\0';
    return 0;
}

static int integer_to_roman(unsigned int value, char *result,
                            size_t result_size)
{
    static const unsigned int numeral_values[] = {
        1000U, 900U, 500U, 400U, 100U, 90U, 50U,
        40U, 10U, 9U, 5U, 4U, 1U
    };
    static const char *const numeral_symbols[] = {
        "M", "CM", "D", "CD", "C", "XC", "L",
        "XL", "X", "IX", "V", "IV", "I"
    };
    size_t position = 0U;
    size_t i;

    if (result == NULL || result_size == 0U ||
        value < 1U || value > 3999U) {
        return 0;
    }

    result[0] = '\0';

    for (i = 0U;
         i < sizeof numeral_values / sizeof numeral_values[0];
         ++i) {
        while (value >= numeral_values[i]) {
            const char *symbol = numeral_symbols[i];

            while (*symbol != '\0') {
                if (position + 1U >= result_size) {
                    result[0] = '\0';
                    return 0;
                }

                result[position++] = *symbol++;
            }

            value -= numeral_values[i];
        }
    }

    result[position] = '\0';
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[INPUT_BUFFER_SIZE] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char roman_buffer[ROMAN_BUFFER_SIZE] = {0};
    char *end = NULL;
    unsigned long value;

    if (!read_input(input_buffer, sizeof input_buffer)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoul(input_buffer, &end, 10);

    if (end == input_buffer || errno == ERANGE ||
        value > (unsigned long)UINT_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end) != 0) {
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

    if (!integer_to_roman((unsigned int)value, roman_buffer,
                          sizeof roman_buffer)) {
        fputs("Conversion failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(roman_buffer) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}