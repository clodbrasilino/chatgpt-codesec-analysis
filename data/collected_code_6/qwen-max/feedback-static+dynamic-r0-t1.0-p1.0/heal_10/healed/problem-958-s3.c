#include <stdio.h>
#include <string.h>

const char *const romanNumerals[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};

char *intToRoman(int num, char *roman, size_t size) {
    *roman = '\0';

    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            size_t len = strlen(roman);
            size_t numeralLen = strlen(romanNumerals[i]);
            if (len + numeralLen < size - 1) {
                strncat(roman, romanNumerals[i], size - len - 1);
                num -= values[i];
            } else {
                break;
            }
        }
    }

    return roman;
}

int main() {
    int number = 1994;
    char roman[20];
    printf("%s\n", intToRoman(number, roman, sizeof(roman)));
    return 0;
}