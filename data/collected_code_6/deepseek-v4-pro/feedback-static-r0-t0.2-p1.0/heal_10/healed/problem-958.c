#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *int_to_roman(int num) {
    if (num <= 0 || num > 3999) {
        return NULL;
    }

    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    const size_t symbol_lens[] = {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1};

    size_t max_len = 0;
    int temp = num;
    for (int i = 0; i < 13; i++) {
        int count = temp / values[i];
        max_len += symbol_lens[i] * (size_t)count;
        temp %= values[i];
    }

    char *result = malloc(max_len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t current_len = 0;
    temp = num;
    for (int i = 0; i < 13; i++) {
        while (temp >= values[i]) {
            size_t symbol_len = symbol_lens[i];
            memcpy(result + current_len, symbols[i], symbol_len);
            current_len += symbol_len;
            temp -= values[i];
        }
    }
    result[current_len] = '\0';

    return result;
}

int main(void) {
    int test_values[] = {1, 4, 9, 58, 1994, 3999, 0, 4000};
    int num_tests = sizeof(test_values) / sizeof(test_values[0]);

    for (int i = 0; i < num_tests; i++) {
        char *roman = int_to_roman(test_values[i]);
        if (roman != NULL) {
            printf("%d -> %s\n", test_values[i], roman);
            free(roman);
        } else {
            printf("%d -> Invalid input\n", test_values[i]);
        }
    }

    return 0;
}