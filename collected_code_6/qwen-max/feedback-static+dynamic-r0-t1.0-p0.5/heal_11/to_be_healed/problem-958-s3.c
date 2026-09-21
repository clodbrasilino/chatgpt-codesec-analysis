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
    memset(roman, 0, 20);

    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

    int index = 0;
    for (int i = 0; num > 0 && i < 13; i++) {
        while (num >= values[i]) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(symbols[i]);
            if (index + len < 20) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(roman + index, symbols[i], len);
                index += len;
            } else {
                free(roman);
                return NULL;
            }
            num -= values[i];
        }
    }

    return roman;
}

int main() {
    /* Possible weaknesses found:
     *  Variable 'numbers' can be declared as const array [constVariable]
     */
    int numbers[] = {1, 4, 50, 51, 100, 104, 500, 900, 1000};
    for (int i = 0; i < 9; i++) {
        char *roman = intToRoman(numbers[i]);
        if (roman) {
            printf("%d in Roman numerals is: %s\n", numbers[i], roman);
            free(roman);
        } else {
            printf("Memory allocation failed for %d.\n", numbers[i]);
        }
    }
    return 0;
}