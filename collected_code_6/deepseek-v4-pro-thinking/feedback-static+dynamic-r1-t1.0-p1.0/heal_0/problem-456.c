#include <stddef.h>
#include <stdio.h>
#include <string.h>

static void reverse_string(char *str)
{
    size_t len;
    size_t i;
    char tmp;

    if (str == NULL) {
        return;
    }

    len = strlen(str);

    for (i = 0; i < len / 2; ++i) {
        tmp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = tmp;
    }
}

void reverse_strings(char *strings[], size_t count)
{
    size_t i;

    if (strings == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        reverse_string(strings[i]);
    }
}

int main(void)
{
    char s1[] = "hello";
    char s2[] = "world";
    char s3[] = "C";
    char *strings[] = { s1, s2, s3 };
    size_t count = sizeof(strings) / sizeof(strings[0]);
    size_t i;

    reverse_strings(strings, count);

    for (i = 0; i < count; ++i) {
        printf("%s\n", strings[i]);
    }

    return 0;
}