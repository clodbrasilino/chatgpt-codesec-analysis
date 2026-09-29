#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* intToRoman(int num) {
    char *roman = (char *)malloc(21 * sizeof(char));
    if (!roman) return NULL;
    roman[0] = '\0';
    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    size_t len = 0;
    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            size_t sym_len = strlen(symbols[i]);
            if (len + sym_len < 20) {
                memcpy(roman + len, symbols[i], sym_len);
                roman[len + sym_len] = '\0';
                len += sym_len;
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
        printf("%d in Roman numerals is: %s\n", number, roman);
        free(roman);
    } else {
        printf("Failed to convert to Roman numeral.\n");
    }
    return 0;
}