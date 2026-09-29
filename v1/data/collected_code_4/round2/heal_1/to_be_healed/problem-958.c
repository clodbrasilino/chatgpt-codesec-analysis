#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strcat'
  */

void intToRoman(int num, char* result) {
    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    char* symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

    while (num > 0) {
        for (int i = 0; i < 13; i++) {
            while (num >= values[i]) {
                num -= values[i];
                /* Possible weaknesses found:
                 *  include '<string.h>' or provide a declaration of 'strcat'
                 *  incompatible implicit declaration of built-in function 'strcat' [-Wbuiltin-declaration-mismatch]
                 *  implicit declaration of function 'strcat' [-Wimplicit-function-declaration]
                 */
                strcat(result, symbols[i]);
            }
        }
    }
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    if (num < 1 || num > 3999) {
        printf("Number out of range. Please enter a number between 1 and 3999.\n");
        return 1;
    }

    char* result = malloc(16);
    if (result == NULL) {
        printf("Memory allocation failed. Exiting program.\n");
        return 1;
    }

    intToRoman(num, result);

    printf("Roman numeral: %s\n", result);

    free(result);
    return 0;
}