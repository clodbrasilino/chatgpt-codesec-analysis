#include <stdio.h>

char first_repeated_char(const char *str)
{
    int count[256] = {0};
    const unsigned char *p;

    if (str == NULL)
        return '\0';

    p = (const unsigned char *)str;

    while (*p) {
        count[*p]++;
        ++p;
    }

    p = (const unsigned char *)str;

    while (*p) {
        if (count[*p] > 1)
            return (char)*p;
        ++p;
    }

    return '\0';
}

int main(void)
{
    const char *str = "hello";
    char result = first_repeated_char(str);

    if (result != '\0')
        printf("First repeated character: %c\n", result);
    else
        printf("No repeated character found\n");

    return 0;
}