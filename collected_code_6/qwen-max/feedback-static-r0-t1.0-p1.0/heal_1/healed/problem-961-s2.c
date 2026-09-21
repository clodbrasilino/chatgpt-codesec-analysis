#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int romanToInt(const char *s) {
    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *roman[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int num = 0;
    const size_t *lengths = (const size_t[]){
        sizeof("M") - 1, sizeof("CM") - 1, sizeof("D") - 1, sizeof("CD") - 1,
        sizeof("C") - 1, sizeof("XC") - 1, sizeof("L") - 1, sizeof("XL") - 1,
        sizeof("X") - 1, sizeof("IX") - 1, sizeof("V") - 1, sizeof("IV") - 1, sizeof("I") - 1
    };

    for (int i = 0; i < 13; ++i) {
        while (strncmp(s, roman[i], lengths[i]) == 0) {
            num += values[i];
            s += lengths[i];
        }
    }

    return num;
}

int main() {
    const char *input = "MCMXCIV";
    printf("%d\n", romanToInt(input));
    return 0;
}