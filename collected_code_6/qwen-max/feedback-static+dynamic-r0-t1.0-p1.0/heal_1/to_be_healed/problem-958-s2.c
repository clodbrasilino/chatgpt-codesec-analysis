#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

char *intToRoman(int num) {
    /* Possible weaknesses found:
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    char *roman = (char *)malloc(20 * sizeof(char));
    if (!roman) return NULL;
    /* Possible weaknesses found:
     *  Variable 's' can be declared as const array [constVariable]
     */
    char *s[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    /* Possible weaknesses found:
     *  Variable 'v' can be declared as const array [constVariable]
     */
    int v[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    /* Possible weaknesses found:
     *  Variable 'i' is assigned a value that is never used. [unreadVariable]
     */
    int i = 0, j;

    for (j = 0; j < 13; j++) {
        while (num >= v[j]) {
            strcat(roman, s[j]);
            num -= v[j];
        }
    }

    return roman;
}

int main() {
    int number = 1994;
    char *result = intToRoman(number);
    if (result) {
        printf("%d in Roman numerals is: %s\n", number, result);
        /* Possible weaknesses found:
         *  include '<stdlib.h>' or provide a declaration of 'free'
         *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
         *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
         */
        free(result);
    } else {
        printf("Failed to convert %d to Roman numeral.\n", number);
    }
    return 0;
}