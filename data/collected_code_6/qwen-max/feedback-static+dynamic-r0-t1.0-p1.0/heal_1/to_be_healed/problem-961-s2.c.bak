#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int romanToInt(char *s) {
    /* Possible weaknesses found:
     *  Variable 'values' can be declared as const array [constVariable]
     */
    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    /* Possible weaknesses found:
     *  Variable 'roman' can be declared as const array [constVariable]
     */
    char *roman[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int i, num = 0;

    for (i = 0; i < 13; ++i) {
        while (strncmp(s, roman[i], strlen(roman[i])) == 0) {
            num += values[i];
            s += strlen(roman[i]);
        }
    }

    return num;
}

int main() {
    char *input = "MCMXCIV";
    printf("%d\n", romanToInt(input));
    return 0;
}