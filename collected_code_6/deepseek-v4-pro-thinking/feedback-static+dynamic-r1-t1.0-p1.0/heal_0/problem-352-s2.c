#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

bool all_unique(const char *str)
{
    if (str == NULL)
    {
        return false;
    }

    bool seen[UCHAR_MAX + 1] = { false };

    for (const char *p = str; *p != '\0'; ++p)
    {
        unsigned char ch = (unsigned char)*p;
        if (seen[ch])
        {
            return false;
        }
        seen[ch] = true;
    }

    return true;
}

int main(void)
{
    const char *s1 = "abcdef";
    const char *s2 = "hello";
    const char *s3 = "";
    const char *s4 = NULL;

    printf("%d\n", all_unique(s1));
    printf("%d\n", all_unique(s2));
    printf("%d\n", all_unique(s3));
    printf("%d\n", all_unique(s4));

    return 0;
}