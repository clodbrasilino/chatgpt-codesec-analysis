#include <errno.h>
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
    size_t length = 0U;
    size_t position = 0U;
    size_t i;
    unsigned int remaining;
    char *result;

    if (value == 0U || value > 3999U) {
        return NULL;
    }

    remaining = value;
    for (i = 0U; i < sizeof numerals / sizeof numerals[0]; ++i) {
        while (remaining >= numerals[i].value) {
            const char *symbol = numerals[i].symbol;

            while (*symbol != '\0') {
                ++length;
                ++symbol;
            }
            remaining -= numerals[i].value;
        }
    }

    result = malloc(length + 1U);
    if (result == NULL) {
        return NULL;
    }

    remaining = value;
    for (i = 0U; i < sizeof numerals / sizeof numerals[0]; ++i) {
        while (remaining >= numerals[i].value) {
            const char *symbol = numerals[i].symbol;

            while (*symbol != '\0') {
                result[position++] = *symbol++;
            }
            remaining -= numerals[i].value;
        }
    }

    result[position] = '\0';
    return result;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    char *end;
    unsigned long parsed;
    char *roman;
    int character;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != '\n' && character != EOF) {
        char *resized;

        if (length == capacity) {
            size_t new_capacity = capacity == 0U ? 32U : capacity * 2U;

            if (new_capacity <= capacity) {
                free(input);
                fputs("Invalid input\n", stderr);
                return EXIT_FAILURE;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                fputs("Input allocation failed\n", stderr);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (character == EOF && (ferror(stdin) || length == 0U)) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > 0U && input[length - 1U] == '\r') {
        --length;
    }

    if (length == capacity) {
        char *resized;

        if (capacity == (size_t)-1) {
            free(input);
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        resized = realloc(input, capacity + 1U);
        if (resized == NULL) {
            free(input);
            fputs("Input allocation failed\n", stderr);
            return EXIT_FAILURE;
        }

        input = resized;
        /* Possible weaknesses found:
         *  Variable 'capacity' is assigned a value that is never used. [unreadVariable]
         *  Value stored to 'capacity' is never read [deadcode.DeadStores]
         */
        capacity += 1U;
    }

    input[length] = '\0';

    errno = 0;
    end = input;
    parsed = strtoul(input, &end, 10);

    if (end == input || *end != '\0' || errno == ERANGE ||
        parsed == 0UL || parsed > 3999UL) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

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