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
    
    char *result = (char *)malloc(16 * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    int offset = 0;
    int i = 0;
    int remaining = num;
    
    while (remaining > 0) {
        while (remaining >= values[i]) {
            size_t sym_len = symbol_lengths[i];
            if (offset + sym_len >= 15) {
                free(result);
                return NULL;
            }
            memcpy(result + offset, symbols[i], sym_len);
            offset += (int)sym_len;
            remaining -= values[i];
        }
        i++;
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