#include <stdio.h>
#include <stdlib.h>

char* intToRoman(int num) {
    if (num < 1 || num > 3999) {
        return NULL;
    }

    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char* const symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    
    char* result = (char*)malloc(20 * sizeof(char));
    if (result == NULL) {
        return NULL;
    }

    int pos = 0;
    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            const char* sym = symbols[i];
            while (*sym != '\0') {
                result[pos++] = *sym++;
            }
            num -= values[i];
        }
    }
    result[pos] = '\0';

    return result;
}

int main(void) {
    int num;
    while (scanf("%d", &num) == 1) {
        char* roman = intToRoman(num);
        if (roman != NULL) {
            printf("%s\n", roman);
            free(roman);
        }
    }
    return 0;
}