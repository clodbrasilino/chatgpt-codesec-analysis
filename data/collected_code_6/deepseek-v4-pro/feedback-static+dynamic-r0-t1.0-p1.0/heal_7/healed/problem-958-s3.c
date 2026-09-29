#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void int_to_roman(int num, char *result, size_t result_size) {
    if (result == NULL || result_size == 0) {
        return;
    }

    if (num <= 0 || num > 3999) {
        result[0] = '\0';
        return;
    }

    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    const size_t symbol_lens[] = {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1};

    result[0] = '\0';
    int remaining = num;
    size_t current_len = 0;

    for (int i = 0; i < 13; i++) {
        while (remaining >= values[i]) {
            size_t sym_len = symbol_lens[i];
            if (current_len + sym_len + 1 > result_size) {
                result[result_size - 1] = '\0';
                return;
            }
            if (current_len + sym_len < result_size) {
                memcpy(result + current_len, symbols[i], sym_len);
                current_len += sym_len;
                result[current_len] = '\0';
            }
            remaining -= values[i];
        }
    }
}

int main(void) {
    int test_numbers[] = {1, 3, 4, 9, 58, 1994, 3999};
    int num_tests = sizeof(test_numbers) / sizeof(test_numbers[0]);
    char roman[20];

    for (int i = 0; i < num_tests; i++) {
        int_to_roman(test_numbers[i], roman, sizeof(roman));
        printf("%d = %s\n", test_numbers[i], roman);
    }

    return 0;
}