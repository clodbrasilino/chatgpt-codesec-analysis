#include <stdio.h>
#include <string.h>

char* int_to_roman(int num) {
    char *roman = (char *)malloc(20 * sizeof(char));
    if (!roman) return NULL;
    roman[0] = '\0';
    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            strcat(roman, symbols[i]);
            num -= values[i];
        }
    }

    return roman;
}

int main() {
    int number = 1994;
    char *roman = int_to_roman(number);
    if (roman != NULL) {
        printf("%s\n", roman);
        free(roman);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}