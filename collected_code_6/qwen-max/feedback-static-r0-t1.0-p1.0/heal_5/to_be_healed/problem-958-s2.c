#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

char* intToRoman(int num) {
    char *roman = (char *)malloc(21 * sizeof(char));
    if (!roman) return NULL;
    roman[0] = '\0';
    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            /* Possible weaknesses found:
             *  call to undeclared function 'strnlen'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  implicit declaration of function 'strnlen' [-Wimplicit-function-declaration]
             */
            size_t len = strnlen(roman, 20);
            /* Possible weaknesses found:
             *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  include the header <string.h> or explicitly provide a declaration for 'strlen'
             */
            size_t sym_len = strlen(symbols[i]);
            if (len + sym_len + 1 < 21) {
                snprintf(roman + len, 21 - len, "%s", symbols[i]);
            }
            num -= values[i];
        }
    }
    return roman;
}

int main() {
    int number = 1994;
    char *roman = intToRoman(number);
    if (roman) {
        printf("%d in roman numerals is: %s\n", number, roman);
        free(roman);
    } else {
        printf("Failed to convert to Roman numeral.\n");
    }
    return 0;
}