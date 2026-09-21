#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROMAN_BUFFER_SIZE 16
#define MIN_ROMAN_VALUE 1
#define MAX_ROMAN_VALUE 3999

int int_to_roman(int value, char *buffer, size_t buffer_size)
{
    static const struct {
        int value;
        const char *numeral;
    } roman_table[] = {
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

    size_t position;
    size_t table_size;
    size_t i;
    size_t numeral_length;

    if (buffer == NULL || buffer_size == 0) {
        return -1;
    }

    if (value < MIN_ROMAN_VALUE || value > MAX_ROMAN_VALUE) {
        buffer[0] = '\0';
        return -1;
    }

    position = 0;
    table_size = sizeof(roman_table) / sizeof(roman_table[0]);

    for (i = 0; i < table_size; i++) {
        while (value >= roman_table[i].value) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            numeral_length = strlen(roman_table[i].numeral);
            if (position + numeral_length >= buffer_size) {
                buffer[0] = '\0';
                return -1;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(buffer + position, roman_table[i].numeral, numeral_length);
            position += numeral_length;
            value -= roman_table[i].value;
        }
    }

    buffer[position] = '\0';
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char roman_buffer[ROMAN_BUFFER_SIZE];
    int number;
    int scan_result;
    int conversion_result;

    printf("Enter an integer (1-3999): ");
    scan_result = scanf("%d", &number);

    if (scan_result != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }

    conversion_result = int_to_roman(number, roman_buffer, sizeof(roman_buffer));

    if (conversion_result != 0) {
        fprintf(stderr, "Error: Number must be between 1 and 3999\n");
        return EXIT_FAILURE;
    }

    printf("Roman numeral: %s\n", roman_buffer);

    return EXIT_SUCCESS;
}