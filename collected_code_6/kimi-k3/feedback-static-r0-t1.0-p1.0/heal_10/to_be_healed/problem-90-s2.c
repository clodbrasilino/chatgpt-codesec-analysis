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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[4096];
    size_t longest_length;
    size_t len;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        return 1;
    }

    len = strcspn(buffer, "\n");

    if (len == sizeof(buffer) - 1 && buffer[len] != '\n' && !feof(stdin))
    {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
    }

    buffer[len] = '\0';

    if (find_longest_word_length(buffer, &longest_length) != 0)
    {
        return 1;
    }

    printf("%zu\n", longest_length);

    return 0;
}