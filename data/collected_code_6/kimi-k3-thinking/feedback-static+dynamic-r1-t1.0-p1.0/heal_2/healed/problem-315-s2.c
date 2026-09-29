#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>

int findFirstMaxEvenWordLength(const char *str)
{
    size_t i;
    int curLen = 0;
    int maxLen = 0;

    if (str == NULL)
    {
        return 0;
    }

    for (i = 0; str[i] != '\0'; i++)
    {
        if (!isspace((unsigned char)str[i]))
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

    if (curLen > 0 && (curLen % 2) == 0 && curLen > maxLen)
    {
        maxLen = curLen;
    }

    return maxLen;
}

int main(void)
{
    char *str = NULL;
    size_t capacity = 0;
    ssize_t length;
    int result;

    printf("Enter a sentence: ");

    length = getline(&str, &capacity, stdin);

    if (length < 0)
    {
        fprintf(stderr, "Error: failed to read input.\n");
        free(str);
        return 1;
    }

    str[strcspn(str, "\n")] = '\0';

    result = findFirstMaxEvenWordLength(str);

    if (result > 0)
    {
        printf("Length of the first longest even word: %d\n", result);
    }
    else
    {
        printf("No even-length word found.\n");
    }

    free(str);

    return 0;
}