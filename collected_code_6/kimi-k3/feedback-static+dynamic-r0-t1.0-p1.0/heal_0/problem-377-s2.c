#include <stdio.h>
#include <string.h>

void remove_char(char *str, char c)
{
    if (str == NULL)
    {
        return;
    }

    size_t read_idx = 0;
    size_t write_idx = 0;

    while (str[read_idx] != '\0')
    {
        if (str[read_idx] != c)
        {
            str[write_idx] = str[read_idx];
            write_idx++;
        }
        read_idx++;
    }
    str[write_idx] = '\0';
}

int main(void)
{
    char str[256];
    char c;

    if (fgets(str, sizeof(str), stdin) == NULL)
    {
        return 1;
    }

    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
    {
        str[len - 1] = '\0';
    }

    if (scanf("%c", &c) != 1)
    {
        return 1;
    }

    remove_char(str, c);

    printf("%s\n", str);

    return 0;
}