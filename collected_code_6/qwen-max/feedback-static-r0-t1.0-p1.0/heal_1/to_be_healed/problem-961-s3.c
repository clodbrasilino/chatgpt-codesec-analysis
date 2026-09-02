#include <stdio.h>
#include <string.h>

int romanToInt(char *s) {
    /* Possible weaknesses found:
     *  Variable 'values' can be declared as const array [constVariable]
     */
    int values[13] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    /* Possible weaknesses found:
     *  Variable 'roman' can be declared as const array [constVariable]
     */
    char *roman[13] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    /* Possible weaknesses found:
     *  Unused variable: j [unusedVariable]
     */
    int i, j, num = 0, len = strlen(s);

    for (i = 0; i < 13; i++) {
        while (len >= (strlen(roman[i])) && strncmp(s, roman[i], strlen(roman[i])) == 0) {
            num += values[i];
            s += strlen(roman[i]);
            len -= strlen(roman[i]);
        }
    }
    return num;
}

int main() {
    char romanNumeral[] = "MCMXCIV";
    int result = romanToInt(romanNumeral);
    printf("%d\n", result);
    return 0;
}