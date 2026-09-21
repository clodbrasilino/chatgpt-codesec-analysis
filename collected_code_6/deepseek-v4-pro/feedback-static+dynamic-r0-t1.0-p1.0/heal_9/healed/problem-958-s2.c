#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *int_to_roman(int num) {
    if (num <= 0 || num > 3999) {
        return NULL;
    }

    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    
    const size_t max_roman_length = 16;
    
    char *result = malloc(max_roman_length * sizeof(char));
    if (result == NULL) {
        return NULL;
    }

    size_t pos = 0;
    size_t remaining_space = max_roman_length;
    int i = 0;

    while (num > 0 && i < 13) {
        while (num >= values[i]) {
            const char *sym = symbols[i];
            size_t sym_len = 0;
            while (sym[sym_len] != '\0') {
                sym_len++;
                if (sym_len >= 4) {
                    free(result);
                    return NULL;
                }
            }
            
            if (sym_len >= remaining_space) {
                free(result);
                return NULL;
            }
            
            for (size_t j = 0; j < sym_len && pos < max_roman_length - 1; j++) {
                result[pos++] = sym[j];
                remaining_space--;
            }
            result[pos] = '\0';
            num -= values[i];
        }
        i++;
    }

    return result;
}

int main(void) {
    int test_values[] = {1, 3, 4, 9, 40, 90, 400, 900, 1994, 2023, 3999, 0, -5, 4000};
    int num_tests = sizeof(test_values) / sizeof(test_values[0]);

    for (int i = 0; i < num_tests; i++) {
        printf("%d -> ", test_values[i]);
        char *roman = int_to_roman(test_values[i]);
        if (roman != NULL) {
            printf("%s\n", roman);
            free(roman);
        } else {
            printf("Invalid input (must be 1-3999)\n");
        }
    }

    return 0;
}