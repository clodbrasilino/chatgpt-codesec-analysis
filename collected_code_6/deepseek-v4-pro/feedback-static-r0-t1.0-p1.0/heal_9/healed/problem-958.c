#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *int_to_roman(int num) {
    if (num <= 0 || num > 3999) {
        return NULL;
    }

    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    const size_t symbol_count = sizeof(values) / sizeof(values[0]);
    
    size_t max_len = 0;
    for (size_t i = 0; i < symbol_count; i++) {
        size_t len = 0;
        const char *sym = symbols[i];
        while (sym[len] != '\0') {
            len++;
        }
        if (len > max_len) {
            max_len = len;
        }
    }
    
    size_t buffer_size = 16;
    char *result = (char *)malloc(buffer_size);
    if (result == NULL) {
        return NULL;
    }
    
    result[0] = '\0';
    int remaining = num;
    size_t current_len = 0;
    
    for (size_t i = 0; remaining > 0 && i < symbol_count; i++) {
        while (remaining >= values[i]) {
            size_t sym_len = 0;
            const char *sym = symbols[i];
            while (sym[sym_len] != '\0') {
                sym_len++;
            }
            
            if (current_len + sym_len + 1 > buffer_size) {
                buffer_size = current_len + sym_len + 1;
                char *temp = (char *)realloc(result, buffer_size);
                if (temp == NULL) {
                    free(result);
                    return NULL;
                }
                result = temp;
            }
            
            if (current_len + sym_len < buffer_size) {
                for (size_t j = 0; j < sym_len; j++) {
                    result[current_len + j] = symbols[i][j];
                }
                current_len += sym_len;
                result[current_len] = '\0';
            }
            remaining -= values[i];
        }
    }
    
    return result;
}

int main(void) {
    int test_values[] = {0, 1, 4, 9, 58, 1994, 3549, 3999, 4000, -5};
    int num_tests = sizeof(test_values) / sizeof(test_values[0]);
    
    for (int i = 0; i < num_tests; i++) {
        char *roman = int_to_roman(test_values[i]);
        if (roman != NULL) {
            printf("%d -> %s\n", test_values[i], roman);
            free(roman);
        } else {
            printf("%d -> Invalid input (must be between 1 and 3999)\n", test_values[i]);
        }
    }
    
    return 0;
}