#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *int_to_roman(int num) {
    if (num <= 0 || num > 3999) {
        return NULL;
    }

    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    const size_t symbol_lengths[] = {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1};
    
    size_t max_length = 16;
    char *result = (char *)malloc(max_length * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    size_t offset = 0;
    int remaining = num;
    
    for (int i = 0; i < 13 && remaining > 0; i++) {
        while (remaining >= values[i]) {
            size_t sym_len = symbol_lengths[i];
            if (offset + sym_len + 1 > max_length) {
                size_t new_max_length = max_length * 2;
                if (new_max_length < offset + sym_len + 1) {
                    new_max_length = offset + sym_len + 1;
                }
                char *new_result = (char *)realloc(result, new_max_length * sizeof(char));
                if (new_result == NULL) {
                    free(result);
                    return NULL;
                }
                result = new_result;
                max_length = new_max_length;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + offset, symbols[i], sym_len);
            offset += sym_len;
            remaining -= values[i];
        }
    }
    
    result[offset] = '\0';
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