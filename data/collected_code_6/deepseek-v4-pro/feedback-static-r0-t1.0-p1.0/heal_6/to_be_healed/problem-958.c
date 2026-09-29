#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *int_to_roman(int num) {
    if (num <= 0 || num > 3999) {
        return NULL;
    }

    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    
    char *result = (char *)malloc(16 * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    result[0] = '\0';
    int remaining = num;
    size_t current_len = 0;
    
    for (int i = 0; remaining > 0; i++) {
        while (remaining >= values[i]) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t sym_len = strlen(symbols[i]);
            /* Possible weaknesses found:
             *  Assuming condition 'current_len+sym_len>=15' is false
             */
            if (current_len + sym_len >= 15) {
                free(result);
                return NULL;
            }
            
            /* Possible weaknesses found:
             *  Condition 'current_len+sym_len<15' is always true [knownConditionTrueFalse]
             *  Condition 'current_len+sym_len<15' is always true
             */
            if (current_len + sym_len < 15) {
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(result + current_len, symbols[i], 15 - current_len);
                current_len += sym_len;
                result[current_len] = '\0';
                remaining -= values[i];
            }
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