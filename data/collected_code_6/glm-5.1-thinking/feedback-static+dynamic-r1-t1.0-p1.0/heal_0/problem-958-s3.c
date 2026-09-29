#include <stdio.h>
#include <string.h>
#include <stddef.h>

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

    size_t pos = 0;

    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            size_t sym_len = strlen(symbols[i]);
            if (buf_size - pos <= sym_len) {
                buf[0] = '\0';
                return -1;
            }
            memcpy(buf + pos, symbols[i], sym_len);
            pos += sym_len;
            num -= values[i];
        }
    }

    buf[pos] = '\0';
    return 0;
}

int main(void) {
    char buffer[16];
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