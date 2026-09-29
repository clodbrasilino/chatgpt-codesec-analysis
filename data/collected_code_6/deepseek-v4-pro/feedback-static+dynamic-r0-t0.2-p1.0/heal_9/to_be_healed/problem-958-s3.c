#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *int_to_roman(int num) {
    if (num <= 0 || num > 3999) {
        return NULL;
    }

    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    const size_t symbols_lengths[] = {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1};

    const size_t max_len = 16;
    char *result = malloc(max_len * sizeof(char));
    if (result == NULL) {
        return NULL;
    }

    result[0] = '\0';
    int remaining = num;
    size_t pos = 0;

    for (int i = 0; i < 13; i++) {
        while (remaining >= values[i]) {
            size_t sym_len = symbols_lengths[i];
            if (pos + sym_len >= max_len) {
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + pos, symbols[i], sym_len);
            pos += sym_len;
            remaining -= values[i];
        }
    }

    result[pos] = '\0';
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