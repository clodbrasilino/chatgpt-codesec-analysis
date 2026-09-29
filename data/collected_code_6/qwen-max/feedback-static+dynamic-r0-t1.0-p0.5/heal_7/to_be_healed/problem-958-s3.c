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
    roman[19] = '\0';

    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

    int index = 0;
    for (int i = 0; num > 0; i++) {
        while (num >= values[i]) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(symbols[i]);
            /* Possible weaknesses found:
             * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
             */
            strcpy(roman + index, symbols[i]);
            index += len;
            num -= values[i];
        }
    }

    roman[19] = '\0';
    return roman;
}

int main() {
    int number = 1;
    char *roman = intToRoman(number);
    if (roman) {
        printf("%d in Roman numerals is: %s\n", number, roman);
        free(roman);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}