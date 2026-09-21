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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[256];
    char c;

    if (fgets(str, sizeof(str), stdin) == NULL)
    {
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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