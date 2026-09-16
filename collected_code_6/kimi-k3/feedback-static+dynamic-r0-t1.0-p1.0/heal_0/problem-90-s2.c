#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int find_longest_word_length(const char *str, size_t *out_length)
{
    size_t max_len = 0;
    size_t current_len = 0;
    int in_word = 0;

    if (str == NULL || out_length == NULL)
    {
        return -1;
    }

    while (*str != '\0')
    {
        if (isalpha((unsigned char)*str))
        {
            if (!in_word)
            {
                in_word = 1;
                current_len = 1;
            }
            else
            {
                current_len++;
            }
        }
        else
        {
            if (in_word)
            {
                if (current_len > max_len)
                {
                    max_len = current_len;
                }
                in_word = 0;
                current_len = 0;
            }
        }
        str++;
    }

    if (in_word && current_len > max_len)
    {
        max_len = current_len;
    }

    *out_length = max_len;
    return 0;
}

int main(void)
{
    char buffer[1024];
    size_t longest_length;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        return 1;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    if (find_longest_word_length(buffer, &longest_length) != 0)
    {
        return 1;
    }

    printf("%zu\n", longest_length);

    return 0;
}