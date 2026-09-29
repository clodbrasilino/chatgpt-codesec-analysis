#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROMAN_LENGTH 16
#define MIN_ROMAN_VALUE 1
#define MAX_ROMAN_VALUE 3999

#define SUCCESS 0
#define ERROR_INVALID_INPUT -1
#define ERROR_BUFFER_TOO_SMALL -2

typedef struct {
    int value;
    const char *symbol;
} RomanNumeral;

int convert_to_roman(int num, char *buffer, size_t buffer_size);

int convert_to_roman(int num, char *buffer, size_t buffer_size) {
    if (num < MIN_ROMAN_VALUE || num > MAX_ROMAN_VALUE || buffer == NULL) {
        return ERROR_INVALID_INPUT;
    }

    if (buffer_size < MAX_ROMAN_LENGTH) {
        return ERROR_BUFFER_TOO_SMALL;
    }

    const RomanNumeral roman_numerals[] = {
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
        {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
        {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
    };

    size_t num_roman_symbols = sizeof(roman_numerals) / sizeof(roman_numerals[0]);
    size_t buffer_index = 0;

    for (size_t i = 0; i < num_roman_symbols; i++) {
        while (num >= roman_numerals[i].value) {
            size_t symbol_length = strlen(roman_numerals[i].symbol);
            if (buffer_index + symbol_length >= buffer_size) {
                return ERROR_BUFFER_TOO_SMALL;
            }
            strcpy(&buffer[buffer_index], roman_numerals[i].symbol);
            buffer_index += symbol_length;
            num -= roman_numerals[i].value;
        }
    }
    
    buffer[buffer_index] = '\0';
    return SUCCESS;
}

int main(void) {
    int test_numbers[] = {1, 4, 9, 58, 1994, 2024, 3999, 0, 4000, -10};
    size_t num_tests = sizeof(test_numbers) / sizeof(test_numbers[0]);
    char roman_buffer[MAX_ROMAN_LENGTH];

    for (size_t i = 0; i < num_tests; i++) {
        int status = convert_to_roman(test_numbers[i], roman_buffer, sizeof(roman_buffer));
        if (status == SUCCESS) {
            printf("%d -> %s\n", test_numbers[i], roman_buffer);
        } else {
            fprintf(stderr, "Conversion failed for %d (Error code: %d)\n", test_numbers[i], status);
        }
    }

    return EXIT_SUCCESS;
}