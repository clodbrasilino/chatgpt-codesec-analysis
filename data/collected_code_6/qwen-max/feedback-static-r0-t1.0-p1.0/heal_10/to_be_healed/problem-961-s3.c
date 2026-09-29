#include <stdio.h>
#include <string.h>

int romanToInt(const char *s, size_t len) {
    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *roman[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int num = 0;
    for (size_t i = 0; i < 13; ++i) {
        const char *r = roman[i];
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t r_len = strlen(r);
        while (len >= r_len && strncmp(s, r, r_len) == 0) {
            num += values[i];
            s += r_len;
            len -= r_len;
        }
    }
    return num;
}

int main() {
    /* Possible weaknesses found:
     *  Assignment 'romanNumeral="MCMXCIV"', assigned value is "MCMXCIV"
     */
    const char *romanNumeral = "MCMXCIV";
    /* Possible weaknesses found:
     *  Assignment 'len=strlen(romanNumeral)', assigned value is 7
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(romanNumeral);
    /* Possible weaknesses found:
     *  Condition 'len>0' is always true
     *  Condition 'len>0' is always true [knownConditionTrueFalse]
     */
    if (len > 0) {
        int result = romanToInt(romanNumeral, len);
        printf("%d\n", result);
    }
    return 0;
}