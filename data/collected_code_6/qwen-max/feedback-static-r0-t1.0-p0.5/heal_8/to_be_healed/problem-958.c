#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* intToRoman(int num) {
    char *roman = (char *)malloc(20 * sizeof(char));
    if (!roman) return NULL;
    roman[0] = '\0';
    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(roman);
            /* Possible weaknesses found:
             * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
             */
            strcpy(roman + len, symbols[i]);
            num -= values[i];
        }
    }
    return roman;
}

int main() {
    int number = 1994;
    char *romanNumeral = intToRoman(number);
    if (romanNumeral != NULL) {
        printf("%d in Roman numerals is: %s\n", number, romanNumeral);
        free(romanNumeral);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}