#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

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
    const size_t sym_lens[] = {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1};

    size_t pos = 0;

    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            if (buf_size - pos <= sym_lens[i]) {
                buf[0] = '\0';
                return -1;
            }
            for (size_t j = 0; j < sym_lens[i]; j++) {
                buf[pos++] = symbols[i][j];
            }
            num -= values[i];
        }
    }

    buf[pos] = '\0';
    return 0;
}

int main(void) {
    size_t buf_size = 16;
    char *buffer = malloc(buf_size);
    if (buffer == NULL) {
        return 1;
    }

    int test_cases[] = {3999, 58, 1994, 0, -1, 4000};
    size_t num_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_cases; i++) {
        int num = test_cases[i];
        if (int_to_roman(num, buffer, buf_size) == 0) {
            printf("%d: %s\n", num, buffer);
        } else {
            printf("%d: Invalid input or buffer too small\n", num);
        }
    }

    free(buffer);
    return 0;
}