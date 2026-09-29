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
    /* Possible weaknesses found:
     *  Variable 'symbols' can be declared as const array [constVariable]
     */
    char* symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    
    char* roman = (char*)malloc(16 * sizeof(char));
    if (roman == NULL) {
        return NULL;
    }
    roman[0] = '\0';

    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            num -= values[i];
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            strncat(roman, symbols[i], 16 - strlen(roman) - 1);
        }
    }

    return roman;
}

int main(void) {
    int number = 1994;
    char* romanNumeral = intToRoman(number);

    if (romanNumeral != NULL) {
        printf("%s\n", romanNumeral);
        free(romanNumeral);
        romanNumeral = NULL;
    }

    return 0;
}