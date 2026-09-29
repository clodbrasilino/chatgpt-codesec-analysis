#include <stdio.h>
#include <string.h>

int romanToInt(char *s) {
    /* Possible weaknesses found:
     *  Variable 'values' can be declared as const array [constVariable]
     */
    int values[13] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    /* Possible weaknesses found:
     *  Variable 'roman' can be declared as const array [constVariable]
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char *roman[13] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    /* Possible weaknesses found:
     *  Unused variable: j [unusedVariable]
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int i, j, num = 0, len = strlen(s);

    for (i = 0; i < 13; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        while (len >= (strlen(roman[i])) && strncmp(s, roman[i], strlen(roman[i])) == 0) {
            num += values[i];
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            s += strlen(roman[i]);
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
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