#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROMAN_LENGTH 32
#define MIN_ROMAN_VALUE 1
#define MAX_ROMAN_VALUE 3999

#define SUCCESS 0
#define ERROR_INVALID_INPUT -1
#define ERROR_BUFFER_TOO_SMALL -2

typedef struct {
    int value;
    const char *symbol;
    size_t length;
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
        {1000, "M", 1}, {900, "CM", 2}, {500, "D", 1}, {400, "CD", 2},
        {100, "C", 1}, {90, "XC", 2}, {50, "L", 1}, {40, "XL", 2},
        {10, "X", 1}, {9, "IX", 2}, {5, "V", 1}, {4, "IV", 2}, {1, "I", 1}
    };

    size_t num_roman_symbols = sizeof(roman_numerals) / sizeof(roman_numerals[0]);
    size_t buffer_index = 0;

    for (size_t i = 0; i < num_roman_symbols; i++) {
        while (num >= roman_numerals[i].value) {
            size_t symbol_length = roman_numerals[i].length;
            
            if (buffer_index + symbol_length >= buffer_size) {
                return ERROR_BUFFER_TOO_SMALL;
            }
            
            memcpy(&buffer[buffer_index], roman_numerals[i].symbol, symbol_length);
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
    
    char *roman_buffer = (char *)malloc(MAX_ROMAN_LENGTH * sizeof(char));
    if (roman_buffer == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < num_tests; i++) {
        int status = convert_to_roman(test_numbers[i], roman_buffer, MAX_ROMAN_LENGTH);
        if (status == SUCCESS) {
            printf("%d -> %s\n", test_numbers[i], roman_buffer);
        } else {
            fprintf(stderr, "Conversion failed for %d (Error code: %d)\n", test_numbers[i], status);
        }
    }

    free(roman_buffer);
    return EXIT_SUCCESS;
}