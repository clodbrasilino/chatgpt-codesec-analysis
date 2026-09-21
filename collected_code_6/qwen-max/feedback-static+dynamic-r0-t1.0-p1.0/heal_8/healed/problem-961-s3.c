#include <stdio.h>
#include <string.h>

int romanToInt(const char *s, size_t len) {
    const int values[13] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *roman[13] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int num = 0;
    size_t lens[13];

    for (int i = 0; i < 13; i++) {
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
    const char *romanNumeral = "MCMXCIV";
    size_t len = strlen(romanNumeral);

    if (len > 0) {
        int result = romanToInt(romanNumeral, len);
        printf("%d\n", result);
    } else {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    return 0;
}