#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'EXIT_FAILURE' is defined in header '<stdlib.h>'; this is probably fixable by adding '#include <stdlib.h>'
  */

static int roman_value(char symbol)
{
    switch (symbol) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return 0;
    }
}

static int integer_to_roman(int value, char *buffer, size_t buffer_size)
{
    static const struct {
        int value;
        const char *symbol;
    } table[] = {
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
        {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
        {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
    };

    size_t position = 0U;

    if (value < 1 || value > 3999 || buffer == NULL || buffer_size == 0U) {
        return EINVAL;
    }

    for (size_t i = 0U; i < sizeof(table) / sizeof(table[0]); ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t symbol_length = strlen(table[i].symbol);

        while (value >= table[i].value) {
            if (symbol_length >= buffer_size - position) {
                buffer[0] = '\0';
                return ERANGE;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(buffer + position, table[i].symbol, symbol_length);
            position += symbol_length;
            value -= table[i].value;
        }
    }

    buffer[position] = '\0';
    return 0;
}

static int roman_to_integer(const char *roman, int *result)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char normalized[16];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char canonical[16];
    size_t length;
    int total = 0;

    if (roman == NULL || result == NULL) {
        return EINVAL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(roman);
    if (length == 0U || length >= sizeof(normalized)) {
        return EINVAL;
    }

    for (size_t i = 0U; i < length; ++i) {
        unsigned char character = (unsigned char)roman[i];
        char symbol = (char)toupper(character);

        if (roman_value(symbol) == 0) {
            return EINVAL;
        }

        normalized[i] = symbol;
    }
    normalized[length] = '\0';

    for (size_t i = 0U; i < length; ++i) {
        int current = roman_value(normalized[i]);
        int next = i + 1U < length ? roman_value(normalized[i + 1U]) : 0;

        if (current < next) {
            if (total > INT_MAX + current) {
                return ERANGE;
            }
            total -= current;
        } else {
            if (total > INT_MAX - current) {
                return ERANGE;
            }
            total += current;
        }
    }

    if (integer_to_roman(total, canonical, sizeof(canonical)) != 0 ||
        strcmp(normalized, canonical) != 0) {
        return EINVAL;
    }

    *result = total;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    int value;
    int status;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s ROMAN_NUMERAL\n", argv[0]);
        /* Possible weaknesses found:
         *  each undeclared identifier is reported only once for each function it appears in
         *  'EXIT_FAILURE' undeclared (first use in this function)
         *  use of undeclared identifier 'EXIT_FAILURE'
         */
        return EXIT_FAILURE;
    }

    status = roman_to_integer(argv[1], &value);
    if (status != 0) {
        fprintf(stderr, "Invalid Roman numeral: %s\n", argv[1]);
        /* Possible weaknesses found:
         *  use of undeclared identifier 'EXIT_FAILURE'
         */
        return EXIT_FAILURE;
    }

    if (printf("%d\n", value) < 0) {
        /* Possible weaknesses found:
         *  use of undeclared identifier 'EXIT_FAILURE'
         */
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  'EXIT_SUCCESS' is defined in header '<stdlib.h>'; this is probably fixable by adding '#include <stdlib.h>'
     *  'EXIT_SUCCESS' undeclared (first use in this function)
     *  use of undeclared identifier 'EXIT_SUCCESS'
     */
    return EXIT_SUCCESS;
}