#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 128U

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
    enum { RESULT_SIZE = 16 };
    char *result;
    size_t position = 0U;
    size_t i;

    if (value == 0U || value > 3999U) {
        errno = EDOM;
        return NULL;
    }

    result = malloc(RESULT_SIZE);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0U; i < sizeof numerals / sizeof numerals[0]; ++i) {
        while (value >= numerals[i].value) {
            const char *symbol = numerals[i].symbol;

            while (*symbol != '\0') {
                if (position >= RESULT_SIZE - 1U) {
                    free(result);
                    errno = EOVERFLOW;
                    return NULL;
                }

                result[position++] = *symbol++;
            }

            value -= numerals[i].value;
        }
    }

    result[position] = '\0';
    return result;
}

static int discard_line(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    return ch;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE];
    char *end;
    char *roman;
    unsigned long parsed;
    size_t length;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    for (length = 0U; input[length] != '\0'; ++length) {
    }

    if (length > 0U && input[length - 1U] == '\n') {
        input[length - 1U] = '\0';
    } else if (length == sizeof input - 1U) {
        if (discard_line() != '\n') {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed = strtoul(input, &end, 10);

    if (end == input || errno == ERANGE || parsed < 1UL || parsed > 3999UL) {
        fputs("Value must be from 1 to 3999\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    roman = integer_to_roman((unsigned int)parsed);
    if (roman == NULL) {
        if (errno == EDOM) {
            fputs("Value must be from 1 to 3999\n", stderr);
        } else {
            perror("Unable to convert value");
        }
        return EXIT_FAILURE;
    }

    if (printf("%s\n", roman) < 0) {
        free(roman);
        return EXIT_FAILURE;
    }

    free(roman);
    return EXIT_SUCCESS;
}