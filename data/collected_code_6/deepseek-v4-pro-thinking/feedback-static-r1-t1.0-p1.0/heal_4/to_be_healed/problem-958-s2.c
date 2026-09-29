#include <stddef.h>
#include <stdio.h>
#include <string.h>

int int_to_roman(int num, char *buf, size_t size) {
    if (buf == NULL || size == 0) {
        return -1;
    }
    if (num <= 0 || num >= 4000) {
        return -1;
    }

    static const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    static const char * const symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    static const size_t lengths[] = {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1};

    size_t pos = 0;
    buf[0] = '\0';

    for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        while (num >= values[i]) {
            size_t len = lengths[i];
            if (pos + len + 1 > size) {
                return -1;
            }
            for (size_t j = 0; j < len; j++) {
                buf[pos + j] = symbols[i][j];
            }
            pos += len;
            buf[pos] = '\0';
            num -= values[i];
        }
    }

    return 0;
}

int main(void) {
    int test_values[] = {1, 4, 9, 49, 99, 499, 999, 1999, 3999, 3888};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buf[64];

    for (size_t i = 0; i < sizeof(test_values) / sizeof(test_values[0]); i++) {
        if (int_to_roman(test_values[i], buf, sizeof(buf)) == 0) {
            printf("%d = %s\n", test_values[i], buf);
        } else {
            printf("%d = error\n", test_values[i]);
        }
    }

    return 0;
}