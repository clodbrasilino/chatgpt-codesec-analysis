#include <stdio.h>
#include <string.h>
#include <ctype.h>

int findFirstMaxEvenWordLength(const char *str)
{
    size_t i;
    size_t len;
    int curLen = 0;
    int maxLen = 0;

    if (str == NULL)
    {
        return 0;
    }

    len = strlen(str);

    for (i = 0; i <= len; i++)
    {
        if (i < len && !isspace((unsigned char)str[i]))
        {
            curLen++;
        }
        else
        {
            if (curLen > 0 && (curLen % 2) == 0 && curLen > maxLen)
            {
                maxLen = curLen;
            }
            curLen = 0;
        }
    }

    return maxLen;
}

int main(void)
{
    char str[512];
    size_t len;
    int result;

    printf("Enter a sentence: ");

    if (fgets(str, sizeof(str), stdin) == NULL)
    {
        fprintf(stderr, "Error: failed to read input.\n");
        return 1;
    }

    len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
    {
        str[len - 1] = '\0';
    }

    result = findFirstMaxEvenWordLength(str);

    if (result > 0)
    {
        printf("Length of the first longest even word: %d\n", result);
    }
    else
    {
        printf("No even-length word found.\n");
    }

    return 0;
}