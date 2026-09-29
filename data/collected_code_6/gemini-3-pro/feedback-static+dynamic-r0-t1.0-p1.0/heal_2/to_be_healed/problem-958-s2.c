#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'IV', got <no output>
  *  test case 0 failed: expected 'I', got <no output>
  *  test case 1 failed: expected 'L', got <no output>
  */

char* intToRoman(int num) {
    if (num <= 0 || num > 3999) {
        return NULL;
    }

    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char* const symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    
    char* roman = (char*)malloc(16 * sizeof(char));
    if (!roman) {
        return NULL;
    }

    int i = 0;
    char* ptr = roman;
    size_t remaining = 16;

    while (num > 0) {
        while (num >= values[i]) {
            num -= values[i];
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(symbols[i]);
            if (len < remaining) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(ptr, symbols[i], len);
                ptr += len;
                remaining -= len;
            }
        }
        i++;
    }
    *ptr = '\0';

    return roman;
}

int main() {
    int testCases[] = {3, 4, 9, 58, 1994, 0, 4000};
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < numTestCases; i++) {
        char* roman = intToRoman(testCases[i]);
        if (roman) {
            printf("%d -> %s\n", testCases[i], roman);
            free(roman);
        } else {
            printf("%d -> Invalid input or allocation error\n", testCases[i]);
        }
    }

    return 0;
}