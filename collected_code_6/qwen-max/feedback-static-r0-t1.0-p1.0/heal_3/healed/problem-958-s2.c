#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* intToRoman(int num) {
    char *roman = (char *)malloc(21 * sizeof(char));
    if (!roman) return NULL;
    roman[0] = '\0';
    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            size_t len = strlen(roman);
            size_t sym_len = strlen(symbols[i]);
            if (len + sym_len + 1 < 21) {
                strncat(roman, symbols[i], 20 - len - 1);
            }
            num -= values[i];
        }
    }
    return roman;
}

int main() {
    int number = 1994;
    char *roman = intToRoman(number);
    if (roman) {
        printf("%d in roman numerals is: %s\n", number, roman);
        free(roman);
    } else {
        printf("Failed to convert to Roman numeral.\n");
    }
    return 0;
}