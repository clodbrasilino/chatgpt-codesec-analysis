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
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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