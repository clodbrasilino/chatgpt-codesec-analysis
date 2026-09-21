#include <stdio.h>
#include <string.h>

int romanToInt(const char *s) {
    const int values[13] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    const char *roman[13] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int num = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(s);

    for (int i = 0; i < 13; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t rlen = strlen(roman[i]);

        while (len >= rlen && strncmp(s, roman[i], rlen) == 0) {
            num += values[i];
            s += rlen;
            len -= rlen;
        }
    }
    return num;
}

int main() {
    const char *romanNumeral = "MCMXCIV";
    int result = romanToInt(romanNumeral);
    printf("%d\n", result);
    return 0;
}