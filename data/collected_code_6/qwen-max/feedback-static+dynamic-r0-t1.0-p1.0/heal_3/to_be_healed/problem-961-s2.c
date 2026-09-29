#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 3986, got <no output>
  *  test case 1 failed: expected 4000, got <no output>
  *  test case 2 failed: expected 100, got <no output>
  */

int romanToInt(const char *s) {
    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *roman[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    const size_t len[] = {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1};
    int i, num = 0;
    const char *p = s;

    for (i = 0; i < 13; ++i) {
        while (strncmp(p, roman[i], len[i]) == 0) {
            num += values[i];
            p += len[i];
        }
    }

    return num;
}

int main() {
    const char *input = "MCMXCIV";
    printf("%d\n", romanToInt(input));
    return 0;
}