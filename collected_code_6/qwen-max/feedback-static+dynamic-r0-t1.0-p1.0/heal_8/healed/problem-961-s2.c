#include <stdio.h>
#include <string.h>

int romanToInt(const char *s) {
    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *roman[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int i, num = 0;
    size_t len = strlen(s);

    for (i = 0; i < 13 && s - s < len; ++i) {
        const char *q = roman[i];
        const char *p = s;
        while (*q && *p == *q) {
            ++q;
            ++p;
        }
        if (!*q) {
            num += values[i];
            s = p;
        } else {
            s = s + (p - q);
        }
    }

    return num;
}

int main() {
    const char *input = "MCMXCIV";
    printf("%d\n", romanToInt(input));
    return 0;
}