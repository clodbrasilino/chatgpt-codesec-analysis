#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *integer_to_roman(unsigned int value)
{
    static const struct {
        unsigned int value;
        const char *symbol;
        size_t length;
    } numerals[] = {
        {1000U, "M", 1U}, {900U, "CM", 2U}, {500U, "D", 1U},
        {400U, "CD", 2U}, {100U, "C", 1U},  {90U, "XC", 2U},
        {50U, "L", 1U},   {40U, "XL", 2U},  {10U, "X", 1U},
        {9U, "IX", 2U},   {5U, "V", 1U},    {4U, "IV", 2U},
        {1U, "I", 1U}
    };
    enum { RESULT_SIZE = 16 };
    char *result;
    size_t position = 0U;
    const size_t count = sizeof numerals / sizeof numerals[0];

    if (value == 0U || value > 3999U) {
        errno = EDOM;
        return NULL;
    }

    result = malloc(RESULT_SIZE);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0U; i < count; ++i) {
        while (value >= numerals[i].value) {
            if (position > RESULT_SIZE - 1U ||
                numerals[i].length > RESULT_SIZE - 1U - position) {
                free(result);
                errno = EOVERFLOW;
                return NULL;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + position, numerals[i].symbol, numerals[i].length);
            position += numerals[i].length;
            value -= numerals[i].value;
        }
    }

    result[position] = '\0';
    return result;
}

int main(void)
{
    unsigned int value;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char line[128];
    char trailing;
    char *roman;

    fputs("Enter an integer from 1 to 3999: ", stdout);
    fflush(stdout);

    if (fgets(line, sizeof line, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (strchr(line, '\n') == NULL && !feof(stdin)) {
        int ch;

        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (sscanf(line, "%u %c", &value, &trailing) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    roman = integer_to_roman(value);
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