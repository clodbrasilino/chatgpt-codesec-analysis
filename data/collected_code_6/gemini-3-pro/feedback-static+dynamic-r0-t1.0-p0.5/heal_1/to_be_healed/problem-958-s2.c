#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* intToRoman(int num) {
    if (num <= 0 || num > 3999) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  Variable 'values' can be declared as const array [constVariable]
     */
    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char* symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    
    char* result = (char*)malloc(16 * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';

    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            strncat(result, symbols[i], 15 - strlen(result));
            num -= values[i];
        }
    }

    return result;
}

int main(void) {
    int test_numbers[] = {3, 58, 1994, 4000, -5};
    size_t num_tests = sizeof(test_numbers) / sizeof(test_numbers[0]);

    for (size_t i = 0; i < num_tests; i++) {
        char* roman = intToRoman(test_numbers[i]);
        if (roman != NULL) {
            printf("%d: %s\n", test_numbers[i], roman);
            free(roman);
        } else {
            printf("%d: Invalid input or memory allocation failed\n", test_numbers[i]);
        }
    }

    return 0;
}