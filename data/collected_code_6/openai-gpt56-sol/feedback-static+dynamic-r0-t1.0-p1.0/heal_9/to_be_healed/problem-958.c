#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strchr'
  */

#define INPUT_SIZE 128U
#define ROMAN_SIZE 16U

static int integer_to_roman(unsigned int value, char *result, size_t size)
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

    if (result == NULL || size == 0U || value == 0U || value > 3999U) {
        errno = EINVAL;
        return -1;
    }

    result[0] = '\0';

    for (i = 0U; i < sizeof numerals / sizeof numerals[0]; ++i) {
        while (value >= numerals[i].value) {
            const char *symbol = numerals[i].symbol;

            while (*symbol != '\0') {
                if (position + 1U >= size) {
                    result[0] = '\0';
                    errno = EOVERFLOW;
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

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    return ferror(stdin) ? -1 : 0;
}

static int read_input(char *buffer, size_t size)
{
    char *newline;

    if (buffer == NULL || size < 2U || size > (size_t)INT_MAX) {
        errno = EINVAL;
        return -1;
    }

    buffer[0] = '\0';

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strchr'
     *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    newline = strchr(buffer, '\n');
    if (newline != NULL) {
        *newline = '\0';
        return 0;
    }

    if (feof(stdin)) {
        return 0;
    }

    if (discard_line() != 0) {
        buffer[0] = '\0';
        return -1;
    }

    buffer[0] = '\0';
    errno = EOVERFLOW;
    return -1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char roman[ROMAN_SIZE] = {0};
    char *start;
    char *end;
    unsigned long parsed;

    if (read_input(input, sizeof input) != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    start = input;
    while (*start != '\0' && isspace((unsigned char)*start) != 0) {
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

    while (*end != '\0' && isspace((unsigned char)*end) != 0) {
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

    if (puts(roman) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}