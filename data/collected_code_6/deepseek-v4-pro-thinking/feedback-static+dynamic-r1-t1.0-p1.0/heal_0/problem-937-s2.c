#include <stdio.h>
#include <limits.h>

char most_common_char(const char *str)
{
    unsigned int counts[UCHAR_MAX + 1] = {0};
    const unsigned char *p = (const unsigned char *)str;
    unsigned char most = 0;
    unsigned int max = 0;
    int i;

    if (str == NULL)
    {
        return '\0';
    }

    while (*p != '\0')
    {
        counts[*p]++;
        p++;
    }

    for (i = 0; i <= UCHAR_MAX; i++)
    {
        if (counts[i] > max)
        {
            max = counts[i];
            most = (unsigned char)i;
        }
    }

    return (char)most;
}

int main(void)
{
    char str[] = "hello world";

    printf("Most common character: %c\n", most_common_char(str));

    return 0;
}