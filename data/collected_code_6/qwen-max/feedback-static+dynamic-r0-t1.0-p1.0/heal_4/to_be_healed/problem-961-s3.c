#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 3986, got <no output>
  *  test case 1 failed: expected 4000, got <no output>
  *  test case 2 failed: expected 100, got <no output>
  */

int romanToInt(const char *s) {
    const int values[13] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    const char *roman[13] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int num = 0;
    size_t len;

    for (len = 0; s[len] != '\0'; len++) {}

    for (int i = 0; i < 13; i++) {
        size_t rlen = 0;
        while (roman[i][rlen] != '\0') rlen++;

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