#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* intToRoman(int num) {
    if (num < 1 || num > 3999) {
        return NULL;
    }

    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char* const symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    
    char* result = (char*)malloc(16 * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    int pos = 0;
    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            const char* symbol = symbols[i];
            while (*symbol) {
                result[pos++] = *symbol++;
            }
            num -= values[i];
        }
    }
    result[pos] = '\0';

    return result;
}

int main(void) {
    const int test_cases[] = {3, 58, 1994, 0, 4000};
    const int num_test_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_test_cases; i++) {
        char* roman = intToRoman(test_cases[i]);
        if (roman != NULL) {
            printf("%d: %s\n", test_cases[i], roman);
            free(roman);
        } else {
            printf("%d: Invalid input or allocation failure\n", test_cases[i]);
        }
    }

    return 0;
}