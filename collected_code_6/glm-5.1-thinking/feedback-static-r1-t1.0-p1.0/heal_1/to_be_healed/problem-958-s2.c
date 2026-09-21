#include <stdio.h>
#include <string.h>

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
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t sym_len = strlen(symbols[i]);
            if (pos + sym_len >= buf_size) {
                buf[pos] = '\0';
                return -2;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(buf + pos, symbols[i], sym_len);
            pos += sym_len;
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    int numbers[] = {3, 58, 1994, 0, -1, 4000};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);

    for (size_t i = 0; i < count; i++) {
        int number = numbers[i];
        if (int_to_roman(number, buffer, sizeof(buffer)) == 0) {
            printf("%d -> %s\n", number, buffer);
        } else {
            fprintf(stderr, "Error converting %d\n", number);
        }
    }

    return 0;
}