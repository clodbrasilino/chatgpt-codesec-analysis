#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool all_chars_same(const char *str)
{
    size_t len;
    size_t i;
    char first;

    if (str == NULL)
    {
        return false;
    }

    len = strlen(str);
    if (len == 0)
    {
        return false;
    }

    first = str[0];
    for (i = 1; i < len; i++)
    {
        if (str[i] != first)
        {
            return false;
        }
    }

    return true;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("false\n");
        return 1;
    }

    printf("%s\n", all_chars_same(argv[1]) ? "true" : "false");

    return 0;
}