#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strchr'
  */

#define INPUT_BUFFER_SIZE 128U
#define ROMAN_BUFFER_SIZE 16U

static int discard_remaining_input(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    return ch == '\n';
}

static int read_input(char *buffer, size_t size)
{
    char *newline;

    if (buffer == NULL || size < 2U || size > (size_t)INT_MAX) {
        return 0;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        buffer[0] = '\0';
        return 0;
    }

    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strchr'
     *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    newline = strchr(buffer, '\n');
    if (newline != NULL) {
        *newline = '\0';
        return 1;
    }

    if (feof(stdin)) {
        return 1;
    }

    (void)discard_remaining_input();
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

    if (result == NULL || result_size == 0U ||
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
    char *input_buffer;
    char *roman_buffer;
    char *start;
    char *end;
    unsigned long value;
    int status = EXIT_FAILURE;

    input_buffer = calloc(INPUT_BUFFER_SIZE, sizeof *input_buffer);
    roman_buffer = calloc(ROMAN_BUFFER_SIZE, sizeof *roman_buffer);

    if (input_buffer == NULL || roman_buffer == NULL) {
        fputs("Memory allocation failed\n", stderr);
        goto cleanup;
    }

    if (!read_input(input_buffer, INPUT_BUFFER_SIZE)) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    start = input_buffer;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '+' || *start == '-') {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    errno = 0;
    value = strtoul(start, &end, 10);

    if (end == start || errno == ERANGE || value > (unsigned long)UINT_MAX) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    if (value < 1UL || value > 3999UL) {
        fputs("Input must be between 1 and 3999\n", stderr);
        goto cleanup;
    }

    if (!integer_to_roman((unsigned int)value, roman_buffer,
                          ROMAN_BUFFER_SIZE)) {
        fputs("Conversion failed\n", stderr);
        goto cleanup;
    }

    if (puts(roman_buffer) == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(roman_buffer);
    free(input_buffer);
    return status;
}