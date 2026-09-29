#include <stdio.h>
#include <string.h>
#include <stddef.h>

int int_to_roman(int num, char *buf, size_t size) {
    struct roman_map {
        int value;
        const char *numeral;
    };
    static const struct roman_map map[] = {
        {1000, "M"},
        {900, "CM"},
        {500, "D"},
        {400, "CD"},
        {100, "C"},
        {90, "XC"},
        {50, "L"},
        {40, "XL"},
        {10, "X"},
        {9, "IX"},
        {5, "V"},
        {4, "IV"},
        {1, "I"}
    };
    size_t pos = 0;
    size_t i;

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
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(map[i].numeral);

            if (pos + len >= size) {
                return -1;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(buf + pos, map[i].numeral, len);
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
    char buf[64];

    for (i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        if (int_to_roman(values[i], buf, sizeof(buf)) == 0) {
            printf("%d = %s\n", values[i], buf);
        } else {
            printf("%d = invalid\n", values[i]);
        }
    }

    return 0;
}