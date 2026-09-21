#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static char *integer_to_roman(unsigned int value)
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[16];
    size_t position = 0U;
    size_t i;
    char *result;

    if (value == 0U || value > 3999U) {
        return NULL;
    }

    for (i = 0U; i < sizeof numerals / sizeof numerals[0]; ++i) {
        while (value >= numerals[i].value) {
            const char *symbol = numerals[i].symbol;

            while (*symbol != '\0') {
                if (position >= sizeof buffer - 1U) {
                    return NULL;
                }
                buffer[position++] = *symbol++;
            }

            value -= numerals[i].value;
        }
    }

    buffer[position] = '\0';

    result = malloc(position + 1U);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0U; i <= position; ++i) {
        result[i] = buffer[i];
    }

    return result;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64];
    char *end;
    unsigned long parsed;
    char *roman;
    int character;
    size_t length = 0U;
    int overflow = 0;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != '\n' && character != EOF) {
        if (length < sizeof input - 1U) {
            input[length++] = (char)character;
        } else {
            overflow = 1;
        }
    }

    if (character == EOF && (ferror(stdin) || length == 0U)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (overflow) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > 0U && input[length - 1U] == '\r') {
        --length;
    }

    input[length] = '\0';

    errno = 0;
    end = input;
    parsed = strtoul(input, &end, 10);

    if (end == input || *end != '\0' || errno == ERANGE ||
        parsed == 0UL || parsed > 3999UL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    roman = integer_to_roman((unsigned int)parsed);
    if (roman == NULL) {
        fputs("Conversion failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", roman) < 0) {
        free(roman);
        return EXIT_FAILURE;
    }

    free(roman);
    return EXIT_SUCCESS;
}