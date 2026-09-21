#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'I', got <no output>
  *  test case 2 failed: expected 'IV', got <no output>
  *  test case 1 failed: expected 'L', got <no output>
  */

char* intToRoman(int num) {
    char *roman = (char *)malloc(20 * sizeof(char));
    if (!roman) return NULL;
    roman[0] = '\0';
    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            strncat(roman, symbols[i], 20 - strlen(roman) - 1);
            num -= values[i];
        }
    }
    return roman;
}

int main() {
    int number = 1994;
    char *roman = intToRoman(number);
    if (roman) {
        printf("%d in Roman numerals is: %s\n", number, roman);
        free(roman);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}