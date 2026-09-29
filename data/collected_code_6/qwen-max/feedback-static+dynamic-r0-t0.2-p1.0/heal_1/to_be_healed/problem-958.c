#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

char* intToRoman(int num) {
    /* Possible weaknesses found:
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
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
        /* Possible weaknesses found:
         *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
         *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
         *  include '<stdlib.h>' or provide a declaration of 'free'
         */
        free(romanNumeral);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}