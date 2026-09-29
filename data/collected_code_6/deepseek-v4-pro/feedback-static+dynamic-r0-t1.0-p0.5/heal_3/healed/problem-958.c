#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROMAN_LENGTH 16

char *int_to_roman(int num) {
    if (num <= 0 || num > 3999) {
        return NULL;
    }

    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

    char *result = malloc(MAX_ROMAN_LENGTH);
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';

    size_t current_len = 0;
    size_t remaining = MAX_ROMAN_LENGTH;

    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            const char *symbol = symbols[i];
            size_t symbol_len = 0;
            while (symbol[symbol_len] != '\0') {
                symbol_len++;
            }
            
            if (symbol_len + 1 > remaining) {
                free(result);
                return NULL;
            }
            
            for (size_t j = 0; j < symbol_len; j++) {
                result[current_len + j] = symbol[j];
            }
            current_len += symbol_len;
            result[current_len] = '\0';
            remaining -= symbol_len;
            
            num -= values[i];
        }
    }

    return result;
}

int main(void) {
    int test_values[] = {1, 4, 9, 58, 1994, 3999, 0, 4000};
    int num_tests = sizeof(test_values) / sizeof(test_values[0]);

    for (int i = 0; i < num_tests; i++) {
        char *roman = int_to_roman(test_values[i]);
        if (roman != NULL) {
            printf("%d -> %s\n", test_values[i], roman);
            free(roman);
        } else {
            printf("%d -> Invalid input\n", test_values[i]);
        }
    }

    return 0;
}