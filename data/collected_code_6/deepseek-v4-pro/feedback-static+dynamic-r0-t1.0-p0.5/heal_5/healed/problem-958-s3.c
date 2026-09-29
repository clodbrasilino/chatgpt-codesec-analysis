#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void int_to_roman(int num, char *result, size_t result_size) {
    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    const size_t symbol_count = sizeof(values) / sizeof(values[0]);

    if (result_size > 0) {
        result[0] = '\0';
    } else {
        return;
    }

    size_t current_len = 0;

    for (size_t i = 0; i < symbol_count; i++) {
        while (num >= values[i]) {
            size_t sym_len = strlen(symbols[i]);
            if (current_len + sym_len >= result_size) {
                return;
            }
            memcpy(result + current_len, symbols[i], sym_len);
            current_len += sym_len;
            result[current_len] = '\0';
            num -= values[i];
        }
    }
}

int main(void) {
    int numbers[] = {1, 4, 9, 58, 1994, 2023, 3999};
    int count = sizeof(numbers) / sizeof(numbers[0]);
    char roman[32];

    for (int i = 0; i < count; i++) {
        if (sizeof(roman) > 0) {
            memset(roman, 0, sizeof(roman));
            int_to_roman(numbers[i], roman, sizeof(roman));
            printf("%d = %s\n", numbers[i], roman);
        }
    }

    return 0;
}