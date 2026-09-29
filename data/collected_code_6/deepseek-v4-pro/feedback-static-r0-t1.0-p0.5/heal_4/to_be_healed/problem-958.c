#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *int_to_roman(int num) {
    if (num <= 0 || num > 3999) {
        return NULL;
    }

    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

    size_t buffer_size = 16;
    char *result = malloc(buffer_size);
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';

    size_t current_len = 0;

    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t symbol_len = strlen(symbols[i]);
            size_t remaining = buffer_size - current_len;

            if (symbol_len >= remaining) {
                size_t new_size = buffer_size * 2;
                if (new_size < buffer_size) {
                    free(result);
                    return NULL;
                }
                char *new_result = realloc(result, new_size);
                if (new_result == NULL) {
                    free(result);
                    return NULL;
                }
                result = new_result;
                buffer_size = new_size;
                /* Possible weaknesses found:
                 *  Variable 'remaining' is assigned a value that is never used. [unreadVariable]
                 *  Value stored to 'remaining' is never read [deadcode.DeadStores]
                 */
                remaining = buffer_size - current_len;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + current_len, symbols[i], symbol_len);
            current_len += symbol_len;
            result[current_len] = '\0';
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