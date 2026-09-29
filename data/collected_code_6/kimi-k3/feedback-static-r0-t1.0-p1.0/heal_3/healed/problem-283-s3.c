#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool check_digit_frequency(const char *num_str, size_t max_len)
{
    if (num_str == NULL || max_len == 0)
    {
        return false;
    }

    size_t len = 0;
    while (len < max_len && num_str[len] != '\0')
    {
        len++;
    }

    if (len == 0)
    {
        return false;
    }

    int freq[10] = {0};

    for (size_t i = 0; i < len; i++)
    {
        if (num_str[i] < '0' || num_str[i] > '9')
        {
            return false;
        }
        freq[num_str[i] - '0']++;
    }

    for (int i = 0; i < 10; i++)
    {
        if (freq[i] > 0 && freq[i] > i)
        {
            return false;
        }
    }

    return true;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t len;

    len = getline(&input, &capacity, stdin);

    if (len == -1)
    {
        printf("Invalid\n");
        free(input);
        return 0;
    }

    if (len > 0 && input[len - 1] == '\n')
    {
        input[len - 1] = '\0';
        len--;
    }

    if (check_digit_frequency(input, (size_t)len + 1))
    {
        printf("Valid\n");
    }
    else
    {
        printf("Invalid\n");
    }

    free(input);
    return 0;
}