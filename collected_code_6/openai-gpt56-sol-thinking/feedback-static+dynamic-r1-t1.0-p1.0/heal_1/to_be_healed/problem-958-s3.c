#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROMAN_MAX_VALUE 3999
#define ROMAN_BUFFER_SIZE 16

typedef struct {
    int value;
    const char *numeral;
} RomanMapping;

bool integer_to_roman(int value, char *buffer, size_t buffer_size)
{
    static const RomanMapping mappings[] = {
        {1000, "M"},
        {900, "CM"},
        {500, "D"},
        {400, "CD"},
        {100, "C"},
        {90, "XC"},
        {50, "L"},
        {40, "XL"},
        {10, "X"},
        {9, "IX"},
        {5, "V"},
        {4, "IV"},
        {1, "I"}
    };
    size_t position = 0;
    size_t i;

    if (buffer == NULL || buffer_size == 0) {
        return false;
    }

    buffer[0] = '\0';

    if (value < 1 || value > ROMAN_MAX_VALUE) {
        return false;
    }

    for (i = 0; i < sizeof(mappings) / sizeof(mappings[0]); ++i) {
        while (value >= mappings[i].value) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t numeral_length = strlen(mappings[i].numeral);

            if (numeral_length >= buffer_size - position) {
                buffer[0] = '\0';
                return false;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(buffer + position, mappings[i].numeral, numeral_length);
            position += numeral_length;
            value -= mappings[i].value;
        }
    }

    buffer[position] = '\0';
    return true;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *end = NULL;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char roman[ROMAN_BUFFER_SIZE];
    long value;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer from 1 to %d>\n", argv[0],
                ROMAN_MAX_VALUE);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtol(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        value < 1 || value > ROMAN_MAX_VALUE || value > INT_MAX) {
        fprintf(stderr, "Invalid integer: expected a value from 1 to %d\n",
                ROMAN_MAX_VALUE);
        return EXIT_FAILURE;
    }

    if (!integer_to_roman((int)value, roman, sizeof(roman))) {
        fprintf(stderr, "Failed to convert the integer to a Roman numeral\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", roman) < 0) {
        fprintf(stderr, "Failed to write output\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}