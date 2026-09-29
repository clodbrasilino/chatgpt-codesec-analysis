#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROMAN_MAX_VALUE 3999U
#define ROMAN_BUFFER_SIZE 16U

typedef struct {
    unsigned int value;
    const char *symbol;
    size_t length;
} RomanMapping;

bool integer_to_roman(unsigned int value, char *output, size_t output_size)
{
    static const RomanMapping mappings[] = {
        {1000U, "M", 1U},
        {900U, "CM", 2U},
        {500U, "D", 1U},
        {400U, "CD", 2U},
        {100U, "C", 1U},
        {90U, "XC", 2U},
        {50U, "L", 1U},
        {40U, "XL", 2U},
        {10U, "X", 1U},
        {9U, "IX", 2U},
        {5U, "V", 1U},
        {4U, "IV", 2U},
        {1U, "I", 1U}
    };
    size_t position = 0U;
    size_t i;

    if (output == NULL || output_size == 0U) {
        return false;
    }

    output[0] = '\0';

    if (value == 0U || value > ROMAN_MAX_VALUE) {
        return false;
    }

    for (i = 0U; i < sizeof(mappings) / sizeof(mappings[0]); ++i) {
        while (value >= mappings[i].value) {
            if (mappings[i].length >= output_size - position) {
                output[0] = '\0';
                return false;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(output + position, mappings[i].symbol, mappings[i].length);
            position += mappings[i].length;
            value -= mappings[i].value;
        }
    }

    output[position] = '\0';
    return true;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long parsed_value;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char roman[ROMAN_BUFFER_SIZE];

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer from 1 to 3999>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_value = strtoul(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        parsed_value == 0UL || parsed_value > ROMAN_MAX_VALUE ||
        parsed_value > UINT_MAX) {
        fprintf(stderr, "Invalid integer: expected a value from 1 to 3999\n");
        return EXIT_FAILURE;
    }

    if (!integer_to_roman((unsigned int)parsed_value, roman, sizeof(roman))) {
        fprintf(stderr, "Failed to convert the integer\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", roman);
    return EXIT_SUCCESS;
}