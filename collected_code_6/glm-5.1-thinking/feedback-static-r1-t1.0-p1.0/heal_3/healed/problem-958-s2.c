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
    size_t lens[] = {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1};
    size_t num_symbols = sizeof(values) / sizeof(values[0]);

    size_t pos = 0;

    for (size_t i = 0; i < num_symbols; i++) {
        while (num >= values[i]) {
            if (pos + lens[i] >= buf_size) {
                buf[pos] = '\0';
                return -2;
            }
            for (size_t j = 0; j < lens[i]; j++) {
                buf[pos + j] = symbols[i][j];
            }
            pos += lens[i];
            num -= values[i];
        }
    }

    if (pos >= buf_size) {
        buf[buf_size - 1] = '\0';
        return -2;
    }

    buf[pos] = '\0';
    return 0;
}

int main(void) {
    size_t buffer_size = 64;
    char *buffer = malloc(buffer_size);
    if (buffer == NULL) {
        return 1;
    }

    int numbers[] = {3, 58, 1994, 0, -1, 4000};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);

    for (size_t i = 0; i < count; i++) {
        int number = numbers[i];
        if (int_to_roman(number, buffer, buffer_size) == 0) {
            printf("%d -> %s\n", number, buffer);
        } else {
            fprintf(stderr, "Error converting %d\n", number);
        }
    }

    free(buffer);
    return 0;
}