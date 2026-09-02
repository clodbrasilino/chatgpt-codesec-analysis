#include <stdio.h>
#include <string.h>

char *intToRoman(int num) {
    /* Possible weaknesses found:
     *  Variable 'romanNumerals' can be declared as const array [constVariable]
     */
    char *romanNumerals[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    /* Possible weaknesses found:
     *  Variable 'values' can be declared as const array [constVariable]
     */
    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    static char roman[20];
    roman[0] = '\0';
    
    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            strcat(roman, romanNumerals[i]);
            num -= values[i];
        }
    }

    return roman;
}

int main() {
    int number = 1994;
    printf("%s\n", intToRoman(number));
    return 0;
}