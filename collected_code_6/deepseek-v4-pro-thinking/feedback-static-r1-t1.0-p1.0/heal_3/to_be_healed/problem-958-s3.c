#include <stdio.h>
#include <string.h>
#include <stddef.h>

#define ROMAN_MAX_STRLEN 15
#define ROMAN_BUF_SIZE (ROMAN_MAX_STRLEN + 1)

int int_to_roman(int num, char *buf, size_t size) {
    struct roman_map {
        int value;
        const char *numeral;
        size_t len;
    };
    static const struct roman_map map[] = {
        {1000, "M",  1},
        {900,  "CM", 2},
        {500,  "D",  1},
        {400,  "CD", 2},
        {100,  "C",  1},
        {90,   "XC", 2},
        {50,   "L",  1},
        {40,   "XL", 2},
        {10,   "X",  1},
        {9,    "IX", 2},
        {5,    "V",  1},
        {4,    "IV", 2},
        {1,    "I",  1}
    };
    size_t pos = 0;
    size_t i = 0;

    if (buf == NULL || size == 0) {
        return -1;
    }

    if (num < 1 || num > 3999) {
        buf[0] = '\0';
        return -1;
    }

    buf[0] = '\0';

    for (i = 0; i < sizeof(map) / sizeof(map[0]); i++) {
        while (num >= map[i].value) {
            size_t len = map[i].len;
            if (pos + len >= size) {
                return -1;
            }
            for (size_t j = 0; j < len; j++) {
                buf[pos + j] = map[i].numeral[j];
            }
            pos += len;
            buf[pos] = '\0';
            num -= map[i].value;
        }
    }

    return 0;
}

int main(void) {
    int values[] = {1, 4, 9, 58, 1994, 3999, 0, 4000};
    size_t i;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buf[ROMAN_BUF_SIZE];

    for (i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        if (int_to_roman(values[i], buf, sizeof(buf)) == 0) {
            printf("%d = %s\n", values[i], buf);
        } else {
            printf("%d = invalid\n", values[i]);
        }
    }

    return 0;
}