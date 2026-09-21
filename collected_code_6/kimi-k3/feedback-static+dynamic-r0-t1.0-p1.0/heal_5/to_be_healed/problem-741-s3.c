#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool all_chars_same(const char *str, size_t len)
{
    if (str == NULL || len == 0)
    {
        return false;
    }

    char first = str[0];

    for (size_t i = 1; i < len; i++)
    {
        if (str[i] != first)
        {
            return false;
        }
    }

    return true;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    size_t len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
        len--;
    }

    if (all_chars_same(buffer, len))
    {
        printf("All characters are the same.\n");
    }
    else
    {
        printf("Not all characters are the same.\n");
    }

    return 0;
}