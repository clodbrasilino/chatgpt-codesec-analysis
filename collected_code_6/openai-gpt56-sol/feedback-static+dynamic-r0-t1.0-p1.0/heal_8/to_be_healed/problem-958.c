#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 128U
#define ROMAN_SIZE 16U

static int integer_to_roman(unsigned int value, char *result, size_t size)
{
    static const struct {
        unsigned int value;
        const char *symbol;
    } numerals[] = {
        {1000U, "M"},
        {900U, "CM"},
        {500U, "D"},
        {400U, "CD"},
        {100U, "C"},
        {90U, "XC"},
        {50U, "L"},
        {40U, "XL"},
        {10U, "X"},
        {9U, "IX"},
        {5U, "V"},
        {4U, "IV"},
        {1U, "I"}
    };
    size_t position = 0U;
    size_t i;

    if (value == 0U || value > 3999U || result == NULL || size == 0U) {
        errno = EINVAL;
        return -1;
    }

    result[0] = '\0';

    for (i = 0U; i < sizeof numerals / sizeof numerals[0]; ++i) {
        while (value >= numerals[i].value) {
            const char *symbol = numerals[i].symbol;

            while (*symbol != '\0') {
                if (position >= size - 1U) {
                    errno = EOVERFLOW;
                    result[0] = '\0';
                    return -1;
                }

                result[position++] = *symbol++;
            }

            value -= numerals[i].value;
        }
    }

    result[position] = '\0';
    return 0;
}

static int discard_line(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    return ferror(stdin) ? -1 : 0;
}

static int read_input(char *buffer, size_t size)
{
    size_t length = 0U;

    if (buffer == NULL || size < 2U || size > (size_t)INT_MAX) {
        errno = EINVAL;
        return -1;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return -1;
    }

    while (length < size && buffer[length] != '\0') {
        ++length;
    }

    if (length == size) {
        if (discard_line() != 0) {
            return -1;
        }
        errno = EOVERFLOW;
        return -1;
    }

    if (length > 0U && buffer[length - 1U] == '\n') {
        buffer[length - 1U] = '\0';
        return 0;
    }

    if (feof(stdin)) {
        return 0;
    }

    if (discard_line() != 0) {
        return -1;
    }

    errno = EOVERFLOW;
    return -1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char roman[ROMAN_SIZE];
    char *start;
    char *end;
    unsigned long parsed;

    if (read_input(input, sizeof input) != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    start = input;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-' || *start == '+') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoul(start, &end, 10);

    if (end == start || errno == ERANGE || parsed < 1UL || parsed > 3999UL) {
        fputs("Value must be from 1 to 3999\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (integer_to_roman((unsigned int)parsed, roman, sizeof roman) != 0) {
        fputs("Unable to convert value\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", roman) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}