#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
             * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
             */
            strcat(roman, symbols[i]);
            num -= values[i];
        }
    }
    return roman;
}

int main() {
    int number = 1994;
    char *romanNumeral = intToRoman(number);
    if (romanNumeral) {
        printf("%d in Roman numerals is: %s\n", number, romanNumeral);
        free(romanNumeral);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}