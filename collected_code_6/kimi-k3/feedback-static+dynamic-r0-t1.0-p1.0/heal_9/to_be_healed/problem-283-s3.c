#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool check_digit_frequency(const char *num_str, size_t len)
{
    if (num_str == NULL || len == 0)
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];

    if (fgets(input, sizeof(input), stdin) != NULL)
    {
        size_t len = strcspn(input, "\n");
        
        if (len < sizeof(input))
        {
            input[len] = '\0';
            
            if (check_digit_frequency(input, len))
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
    }
    else
    {
        printf("Invalid\n");
    }

    return 0;
}