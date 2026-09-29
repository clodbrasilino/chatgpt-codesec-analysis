#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* intToRoman(int num) {
    char *roman = (char *)malloc(20 * sizeof(char));
    if (!roman) return NULL;
    memset(roman, 0, 20);

    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

    int index = 0;
    for (int i = 0; num > 0; i++) {
        while (num >= values[i]) {
            size_t len = strlen(symbols[i]);
            if (index + len <= 20) {
                memcpy(roman + index, symbols[i], len);
                index += len;
            }
            num -= values[i];
        }
    }

    return roman;
}

int main() {
    int number = 1;
    char *roman = intToRoman(number);
    if (roman) {
        printf("%d in Roman numerals is: %s\n", number, roman);
        free(roman);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}