#include <stdio.h>
#include <string.h>

int romanToInt(const char *s, size_t len) {
    const int values[13] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    const char *roman[13] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int num = 0;
    /* Possible weaknesses found:
     *  Variable 'lens' can be declared as const array [constVariable]
     */
    size_t lens[13] = {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1};

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
    const char *romanNumeral = "MCMXCIV";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(romanNumeral);

    int result = romanToInt(romanNumeral, len);
    printf("%d\n", result);
    return 0;
}