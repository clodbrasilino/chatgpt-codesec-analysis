#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ROMAN_BUF_SIZE 32

int int_to_roman(int num, char *buf, size_t size)
{
    if (buf == NULL || size == 0)
        return -1;
    if (num <= 0 || num >= 4000)
        return -1;

    static const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    static const char * const symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    static const size_t lengths[] = {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1};

    size_t pos = 0;
    buf[0] = '\0';

    for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        while (num >= values[i]) {
            size_t len = lengths[i];
            if (pos + len + 1 > size)
                return -1;
            for (size_t j = 0; j < len; j++) {
                buf[pos++] = symbols[i][j];
            }
            buf[pos] = '\0';
            num -= values[i];
        }
    }

    return 0;
}

int main(void)
{
    int test_values[] = {1, 4, 9, 49, 99, 499, 999, 1999, 3999, 3888};
    char *buf = malloc(ROMAN_BUF_SIZE);
    if (buf == NULL)
        return 1;

    for (size_t i = 0; i < sizeof(test_values) / sizeof(test_values[0]); i++) {
        if (int_to_roman(test_values[i], buf, ROMAN_BUF_SIZE) == 0)
            printf("%d = %s\n", test_values[i], buf);
        else
            printf("%d = error\n", test_values[i]);
    }

    free(buf);
    return 0;
}