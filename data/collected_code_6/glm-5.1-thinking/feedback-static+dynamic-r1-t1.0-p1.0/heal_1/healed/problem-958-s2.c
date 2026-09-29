#include <stdio.h>
#include <stdlib.h>

int int_to_roman(int num, char *buf, size_t buf_size) {
    if (buf == NULL || buf_size == 0) {
        return -1;
    }

    if (num < 1 || num > 3999) {
        buf[0] = '\0';
        return -1;
    }

    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    size_t num_symbols = sizeof(values) / sizeof(values[0]);

    size_t pos = 0;

    for (size_t i = 0; i < num_symbols; i++) {
        while (num >= values[i]) {
            int written = snprintf(buf + pos, buf_size - pos, "%s", symbols[i]);
            if (written < 0 || (size_t)written >= buf_size - pos) {
                buf[pos] = '\0';
                return -2;
            }
            pos += written;
            num -= values[i];
        }
    }

    return 0;
}

int main(void) {
    size_t buf_size = 64;
    char *buffer = malloc(buf_size);
    if (buffer == NULL) {
        return 1;
    }

    int numbers[] = {3, 58, 1994, 0, -1, 4000};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);

    for (size_t i = 0; i < count; i++) {
        int number = numbers[i];
        if (int_to_roman(number, buffer, buf_size) == 0) {
            printf("%d -> %s\n", number, buffer);
        } else {
            fprintf(stderr, "Error converting %d\n", number);
        }
    }

    free(buffer);
    return 0;
}