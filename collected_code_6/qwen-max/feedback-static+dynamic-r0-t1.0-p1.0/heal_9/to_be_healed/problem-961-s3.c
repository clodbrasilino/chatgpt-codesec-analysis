#include <stdio.h>
#include <string.h>

int romanToInt(const char *s, size_t len) {
    const int values[13] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    const char *roman[13] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int num = 0;
    size_t lens[13];

    for (int i = 0; i < 13; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        lens[i] = strlen(roman[i]);
    }

    for (int i = 0; i < 13; i++) {
        while (len >= lens[i] && strncmp(s, roman[i], lens[i]) == 0) {
            num += values[i];
            s += lens[i];
            len -= lens[i];
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
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  Assignment 'len=strlen(romanNumeral)', assigned value is 7
     */
    size_t len = strlen(romanNumeral);

    /* Possible weaknesses found:
     *  Condition 'len>0' is always true
     *  Condition 'len>0' is always true [knownConditionTrueFalse]
     */
    if (len > 0) {
        int result = romanToInt(romanNumeral, len);
        printf("%d\n", result);
    } else {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    return 0;
}