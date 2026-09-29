#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

void int_to_roman(int num, char *result, size_t result_size) {
    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    const size_t symbol_count = sizeof(values) / sizeof(values[0]);

    if (result_size == 0) {
        return;
    }

    result[0] = '\0';
    size_t current_len = 0;

    for (size_t i = 0; i < symbol_count; i++) {
        while (num >= values[i]) {
            size_t sym_len = safe_strlen(symbols[i], 4);
            
            if (current_len + sym_len + 1 > result_size) {
                result[current_len] = '\0';
                return;
            }
            
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + current_len, symbols[i], sym_len);
            current_len += sym_len;
            result[current_len] = '\0';
            num -= values[i];
        }
    }
}

int main(void) {
    int numbers[] = {1, 4, 9, 58, 1994, 2023, 3999};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char roman[32];

    for (size_t i = 0; i < count; i++) {
        memset(roman, 0, sizeof(roman));
        int_to_roman(numbers[i], roman, sizeof(roman));
        printf("%d = %s\n", numbers[i], roman);
    }

    return 0;
}