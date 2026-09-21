#include <stdio.h>
#include <stddef.h>

#define MAX_ROMAN_LENGTH 32

int int_to_roman(int num, char *buf, size_t buf_size) {
    if (buf == NULL || buf_size == 0) {
        return -1;
    }

    if (num < 1 || num > 3999) {
        buf[0] = '\0';
        return -1;
    }

    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    const size_t lengths[] = {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1};
    size_t num_symbols = sizeof(values) / sizeof(values[0]);

    size_t pos = 0;

    for (size_t i = 0; i < num_symbols; i++) {
        while (num >= values[i]) {
            size_t sym_len = lengths[i];
            if (pos + sym_len >= buf_size) {
                buf[0] = '\0';
                return -1;
            }
            for (size_t j = 0; j < sym_len; j++) {
                buf[pos + j] = symbols[i][j];
            }
            pos += sym_len;
            num -= values[i];
        }
    }

    if (pos >= buf_size) {
        buf[0] = '\0';
        return -1;
    }
    buf[pos] = '\0';
    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_ROMAN_LENGTH];
    int test_cases[] = {3999, 58, 1994, 0, -1, 4000};
    size_t num_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_cases; i++) {
        int num = test_cases[i];
        if (int_to_roman(num, buffer, sizeof(buffer)) == 0) {
            printf("%d: %s\n", num, buffer);
        } else {
            printf("%d: Invalid input or buffer too small\n", num);
        }
    }

    return 0;
}