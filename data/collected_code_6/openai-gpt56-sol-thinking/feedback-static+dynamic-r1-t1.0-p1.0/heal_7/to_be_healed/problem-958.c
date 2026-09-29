#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct roman_token {
    int value;
    char first;
    char second;
};

static char *integer_to_roman(int value)
{
    static const struct roman_token tokens[] = {
        {1000, 'M', '\0'},
        {900,  'C', 'M'},
        {500,  'D', '\0'},
        {400,  'C', 'D'},
        {100,  'C', '\0'},
        {90,   'X', 'C'},
        {50,   'L', '\0'},
        {40,   'X', 'L'},
        {10,   'X', '\0'},
        {9,    'I', 'X'},
        {5,    'V', '\0'},
        {4,    'I', 'V'},
        {1,    'I', '\0'}
    };

    const size_t token_count = sizeof tokens / sizeof tokens[0];
    size_t required = 0;
    size_t position = 0;
    int remaining;
    char *result;

    if (value < 1 || value > 3999) {
        return NULL;
    }

    remaining = value;

    for (size_t i = 0; i < token_count; ++i) {
        const size_t count = (size_t)(remaining / tokens[i].value);
        const size_t symbol_length =
            tokens[i].second == '\0' ? 1U : 2U;

        required += count * symbol_length;
        remaining %= tokens[i].value;
    }

    result = malloc(required + 1U);

    if (result == NULL) {
        return NULL;
    }

    remaining = value;

    for (size_t i = 0; i < token_count; ++i) {
        while (remaining >= tokens[i].value) {
            result[position++] = tokens[i].first;

            if (tokens[i].second != '\0') {
                result[position++] = tokens[i].second;
            }

            remaining -= tokens[i].value;
        }
    }

    result[position] = '\0';
    return result;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[const])
{
    const char *input;
    char *end;
    char *roman;
    long value;

    if (argc != 2) {
        fputs("Usage: program <integer from 1 to 3999>\n", stderr);
        return EXIT_FAILURE;
    }

    input = argv[1];
    errno = 0;
    end = NULL;
    value = strtol(input, &end, 10);

    if (errno == ERANGE || end == input || *end != '\0' ||
        value < 1 || value > 3999) {
        fputs("Invalid integer: expected a value from 1 to 3999\n", stderr);
        return EXIT_FAILURE;
    }

    roman = integer_to_roman((int)value);

    if (roman == NULL) {
        fputs("Roman numeral conversion failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(roman) == EOF) {
        free(roman);
        return EXIT_FAILURE;
    }

    free(roman);
    return EXIT_SUCCESS;
}