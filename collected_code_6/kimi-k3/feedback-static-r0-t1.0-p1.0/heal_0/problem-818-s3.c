#include <stdio.h>
#include <ctype.h>

int count_lowercase(const char *str)
{
    int count = 0;
    if (str == NULL)
        return 0;
    while (*str != '\0')
    {
        if (islower((unsigned char)*str))
            count++;
        str++;
    }
    return count;
}

int main(void)
{
    char str[256];
    if (fgets(str, sizeof(str), stdin) != NULL)
    {
        int result = count_lowercase(str);
        printf("%d\n", result);
    }
    return 0;
}