#include <stdio.h>
#include <string.h>

int romanToInt(char *s) {
    const int values[13] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *roman[13] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int num = 0;
    int i = 0;

    while (i < 13) {
        const char *currentRoman = roman[i];
        int rlen = strlen(currentRoman);
        while (strncmp(s, currentRoman, rlen) == 0) {
            num += values[i];
            s += rlen;
        }
        i++;
    }
    return num;
}

int main() {
    char romanNumeral[] = "MCMXCIV";
    printf("%d\n", romanToInt(romanNumeral));

    char test0[] = "MMMCMVIII";
    printf("%d\n", romanToInt(test0));

    char test1[] = "MMMM";
    printf("%d\n", romanToInt(test1));

    char test2[] = "C";
    printf("%d\n", romanToInt(test2));

    return 0;
}