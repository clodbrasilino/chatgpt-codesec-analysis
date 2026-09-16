#include <stdio.h>
#include <stddef.h>
#include <limits.h>

char max_occurring_char(const char *str);

int main(void)
{
    /* Possible weaknesses found:
     *  Variable 'text' can be declared as const array [constVariable]
     */
    char text[] = "hello world";
    char result = max_occurring_char(text);
    printf("%c\n", result);
    return 0;
}

char max_occurring_char(const char *str)
{
    if (str == NULL || *str == '\0') {
        return '\0';
    }

    size_t count[UCHAR_MAX + 1] = {0};
    const unsigned char *p = (const unsigned char *)str;

    while (*p != '\0') {
        ++count[*p];
        ++p;
    }

    size_t max = 0;
    for (size_t i = 0; i <= UCHAR_MAX; ++i) {
        if (count[i] > max) {
            max = count[i];
        }
    }

    const char *s = str;
    while (*s != '\0') {
        if (count[(unsigned char)*s] == max) {
            return *s;
        }
        ++s;
    }

    return '\0';
}