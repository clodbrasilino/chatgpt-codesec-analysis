#include <stdio.h>
#include <stddef.h>
#include <limits.h>

void minimize_length(char *str)
{
    size_t count[UCHAR_MAX + 1] = {0};
    unsigned char *p = (unsigned char *)str;
    unsigned char max_char = 0;
    size_t max_count = 0;
    size_t i;
    char *src;
    char *dst;

    if (str == NULL) {
        return;
    }

    while (*p != '\0') {
        count[*p]++;
        p++;
    }

    for (i = 0; i <= UCHAR_MAX; i++) {
        if (count[i] > max_count) {
            max_count = count[i];
            max_char = (unsigned char)i;
        }
    }

    if (max_count == 0) {
        return;
    }

    src = str;
    dst = str;

    while (*src != '\0') {
        if ((unsigned char)*src != max_char) {
            *dst = *src;
            dst++;
        }
        src++;
    }

    *dst = '\0';
}

int main(void)
{
    char s[] = "hello world";

    minimize_length(s);
    printf("%s\n", s);

    return 0;
}