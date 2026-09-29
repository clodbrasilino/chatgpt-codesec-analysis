#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROMAN_LENGTH 16

char* int_to_roman(int num) {
    if (num < 1 || num > 3999) {
        return NULL;
    }

    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char* symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    const size_t symbol_lens[] = {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1};
    const int num_symbols = sizeof(values) / sizeof(values[0]);

    char* roman = (char*)malloc(MAX_ROMAN_LENGTH);
    if (roman == NULL) {
        return NULL;
    }

    size_t current_len = 0;
    int remaining = num;

    for (int i = 0; i < num_symbols; i++) {
        while (remaining >= values[i]) {
            size_t sym_len = symbol_lens[i];
            if (current_len + sym_len + 1 > MAX_ROMAN_LENGTH) {
                free(roman);
                return NULL;
            }
            memcpy(roman + current_len, symbols[i], sym_len);
            current_len += sym_len;
            remaining -= values[i];
        }
    }

    roman[current_len] = '\0';
    return roman;
}

int main(void) {
    int num = 1994;
    char* roman = int_to_roman(num);
    if (roman != NULL) {
        printf("%d -> %s\n", num, roman);
        free(roman);
    } else {
        printf("Invalid input or memory allocation failed.\n");
    }
    return 0;
}