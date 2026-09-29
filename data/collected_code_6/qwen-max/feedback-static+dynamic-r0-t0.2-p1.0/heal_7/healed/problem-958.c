#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* intToRoman(int num) {
    char *roman = (char *)malloc(20 * sizeof(char));
    if (!roman) return NULL;
    roman[19] = '\0';  // Ensure the string is null-terminated
    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int pos = 0;
    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            size_t len = strlen(symbols[i]);
            if (pos + len < 20) {
                memcpy(roman + pos, symbols[i], len);
                pos += len;
                num -= values[i];
            } else {
                free(roman);
                return NULL;
            }
        }
    }
    return roman;
}

int main() {
    int number = 1994;
    char *romanNumeral = intToRoman(number);
    if (romanNumeral) {
        printf("%d in Roman numerals is: %s\n", number, romanNumeral);
        free(romanNumeral);
    } else {
        printf("Memory allocation failed or buffer overflow.\n");
    }
    return 0;
}