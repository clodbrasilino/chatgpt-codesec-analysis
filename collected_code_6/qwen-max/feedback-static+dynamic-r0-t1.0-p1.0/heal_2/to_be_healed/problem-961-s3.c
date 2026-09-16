#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 100, got <no output>
  *  test case 1 failed: expected 4000, got <no output>
  *  test case 0 failed: expected 3986, got <no output>
  */

int romanToInt(char *s) {
    const int values[13] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *roman[13] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int num = 0, len = strlen(s);

    for (int i = 0; i < 13; i++) {
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