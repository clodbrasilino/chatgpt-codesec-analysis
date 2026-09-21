#include <stdio.h>
#include <stdlib.h>

char* intToRoman(int num) {
    if (num <= 0 || num > 3999) {
        return NULL;
    }

    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *const symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    
    char* roman = (char*)malloc(16);
    if (roman == NULL) {
        return NULL;
    }
    
    int pos = 0;

    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            num -= values[i];
            const char* symbol = symbols[i];
            while (*symbol != '\0') {
                roman[pos++] = *symbol++;
            }
        }
    }
    
    roman[pos] = '\0';

    return roman;
}

int main(void) {
    int number;
    if (scanf("%d", &number) == 1) {
        char* romanNumeral = intToRoman(number);

        if (romanNumeral != NULL) {
            printf("%s\n", romanNumeral);
            free(romanNumeral);
        }
    }

    return 0;
}