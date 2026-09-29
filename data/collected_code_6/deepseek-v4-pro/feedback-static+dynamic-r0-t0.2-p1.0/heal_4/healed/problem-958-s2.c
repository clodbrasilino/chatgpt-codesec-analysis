#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *int_to_roman(int num) {
    if (num <= 0 || num > 3999) {
        return NULL;
    }

    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

    char *result = malloc(16 * sizeof(char));
    if (result == NULL) {
        return NULL;
    }

    size_t current_length = 0;
    size_t remaining = 15;

    for (int i = 0; i < 13; i++) {
        size_t symbol_len = strlen(symbols[i]);
        while (num >= values[i]) {
            if (symbol_len >= remaining) {
                free(result);
                return NULL;
            }
            size_t bytes_to_copy = symbol_len < remaining ? symbol_len : remaining;
            memcpy(result + current_length, symbols[i], bytes_to_copy);
            current_length += bytes_to_copy;
            result[current_length] = '\0';
            remaining -= bytes_to_copy;
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