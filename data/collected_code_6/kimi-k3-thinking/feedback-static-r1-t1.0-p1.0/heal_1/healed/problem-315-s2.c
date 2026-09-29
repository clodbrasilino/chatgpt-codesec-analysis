#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_SIZE 512

int findFirstMaxEvenWordLength(const char *str, size_t maxLen)
{
    size_t i;
    size_t len;
    int curLen = 0;
    int maxWordLen = 0;

    if (str == NULL || maxLen == 0)
    {
        return 0;
    }

    len = strnlen(str, maxLen);

    for (i = 0; i <= len; i++)
    {
        if (i < len && !isspace((unsigned char)str[i]))
        {
            curLen++;
        }
        else
        {
            if (curLen > 0 && (curLen % 2) == 0 && curLen > maxWordLen)
            {
                maxWordLen = curLen;
            }
            curLen = 0;
        }
    }

    return maxWordLen;
}

int main(void)
{
    char str[MAX_INPUT_SIZE];
    size_t len;
    int result;

    printf("Enter a sentence: ");

    if (fgets(str, sizeof(str), stdin) == NULL)
    {
        fprintf(stderr, "Error: failed to read input.\n");
        return 1;
    }

    len = strnlen(str, sizeof(str));
    if (len > 0 && str[len - 1] == '\n')
    {
        str[len - 1] = '\0';
    }

    result = findFirstMaxEvenWordLength(str, sizeof(str));

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