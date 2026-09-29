#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool check_digit_frequency(const char *num_str)
{
    if (num_str == NULL || num_str[0] == '\0')
    {
        return false;
    }

    int freq[10] = {0};
    size_t len = strlen(num_str);

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
    char input[256];

    if (fgets(input, sizeof(input), stdin) != NULL)
    {
        input[strcspn(input, "\n")] = '\0';

        if (check_digit_frequency(input))
        {
            printf("Valid\n");
        }
        else
        {
            printf("Invalid\n");
        }
    }
    else
    {
        printf("Invalid\n");
    }

    return 0;
}