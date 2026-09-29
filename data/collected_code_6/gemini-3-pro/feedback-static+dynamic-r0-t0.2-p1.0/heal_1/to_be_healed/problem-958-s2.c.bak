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
            num -= values[i];
            strncat(result, symbols[i], 15 - strlen(result));
        }
    }

    return result;
}

int main(void) {
    int test_cases[] = {3, 58, 1994, 0, 4000};
    int num_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_cases; i++) {
        char* roman = intToRoman(test_cases[i]);
        if (roman != NULL) {
            printf("%d: %s\n", test_cases[i], roman);
            free(roman);
        } else {
            printf("%d: Invalid input\n", test_cases[i]);
        }
    }

    return 0;
}