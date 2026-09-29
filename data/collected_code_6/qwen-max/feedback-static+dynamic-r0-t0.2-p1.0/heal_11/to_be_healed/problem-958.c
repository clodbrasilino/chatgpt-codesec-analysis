#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'I', got <no output>
  *  test case 2 failed: expected 'IV', got <no output>
  *  test case 1 failed: expected 'L', got <no output>
  */

char* intToRoman(int num) {
    char *roman = (char *)calloc(20, sizeof(char));
    if (!roman) return NULL;
    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int pos = 0;
    for (int i = 0; i < 13 && pos < 19; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        while (num >= values[i] && pos + strlen(symbols[i]) <= 19 - 1) {
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            strncpy(roman + pos, symbols[i], strlen(symbols[i]));
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            pos += strlen(symbols[i]);
            num -= values[i];
        }
    }
    roman[pos] = '\0';
    return roman;
}

int main() {
    int number = 1994;
    char *romanNumeral = intToRoman(number);
    if (romanNumeral) {
        printf("%d in Roman numerals is: %s\n", number, romanNumeral);
        free(romanNumeral);
    } else {
        printf("Memory allocation failed or buffer overflow.\n");
    }
    return 0;
}