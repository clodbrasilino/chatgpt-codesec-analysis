#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* intToRoman(int num) {
    if (num <= 0 || num > 3999) {
        return NULL;
    }

    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char* const symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    
    char* roman = (char*)calloc(16, sizeof(char));
    if (!roman) {
        return NULL;
    }

    int i = 0;
    while (num > 0) {
        while (num >= values[i]) {
            num -= values[i];
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t current_len = strlen(roman);
            size_t remaining = 15 - current_len;
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
             */
            strncat(roman, symbols[i], remaining);
        }
        i++;
    }

    return roman;
}

int main(void) {
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