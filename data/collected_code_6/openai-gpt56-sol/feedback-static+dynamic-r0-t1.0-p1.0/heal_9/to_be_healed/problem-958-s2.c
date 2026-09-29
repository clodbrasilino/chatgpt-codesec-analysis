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

    length = 0U;
    while (length < size && buffer[length] != '\0') {
        ++length;
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
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    ch = fgetc(stdin);
    if (ch == EOF) {
        return 1;
    }

    while (ch != '\n' && ch != EOF) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    buffer[0] = '\0';
    return 0;
}

static int integer_to_roman(unsigned int value, char *result,
                            size_t result_size)
{
    static const struct {
        unsigned int value;
        const char *symbol;
    } numerals[] = {
        {1000U, "M"}, {900U, "CM"}, {500U, "D"}, {400U, "CD"},
        {100U, "C"},  {90U, "XC"},  {50U, "L"},  {40U, "XL"},
        {10U, "X"},   {9U, "IX"},   {5U, "V"},   {4U, "IV"},
        {1U, "I"}
    };
    size_t position = 0U;
    size_t i;

    if (result == NULL || result_size < ROMAN_BUFFER_SIZE ||
        value < 1U || value > 3999U) {
        return 0;
    }

    result[0] = '\0';

    for (i = 0U; i < sizeof numerals / sizeof numerals[0]; ++i) {
        while (value >= numerals[i].value) {
            const char *symbol = numerals[i].symbol;

            while (*symbol != '\0') {
                if (position >= result_size - 1U) {
                    result[0] = '\0';
                    return 0;
                }

                result[position++] = *symbol++;
            }

            value -= numerals[i].value;
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
    char *start = input_buffer;
    char *end = NULL;
    unsigned long value;

    if (!read_input(input_buffer, sizeof input_buffer)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*start != '\0' && isspace((unsigned char)*start) != 0) {
        ++start;
    }

    if (*start == '\0' || *start == '-' || *start == '+') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoul(start, &end, 10);

    if (end == start || errno == ERANGE || value > (unsigned long)UINT_MAX) {
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