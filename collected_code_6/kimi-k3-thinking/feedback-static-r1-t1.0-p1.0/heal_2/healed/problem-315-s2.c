#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>

size_t findFirstMaxEvenWordLength(const char *str, size_t maxLen)
{
    size_t i;
    size_t len;
    size_t curLen = 0;
    size_t maxWordLen = 0;

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
    char *str = NULL;
    size_t capacity = 0;
    ssize_t readLen;
    size_t len;
    size_t result;

    printf("Enter a sentence: ");

    readLen = getline(&str, &capacity, stdin);
    if (readLen < 0)
    {
        fprintf(stderr, "Error: failed to read input.\n");
        free(str);
        return 1;
    }

    len = (size_t)readLen;
    if (len > 0 && str[len - 1] == '\n')
    {
        str[len - 1] = '\0';
        len--;
    }

    result = findFirstMaxEvenWordLength(str, len);

    if (result > 0)
    {
        printf("Length of the first longest even word: %zu\n", result);
    }
    else
    {
        printf("No even-length word found.\n");
    }

    free(str);
    return 0;
}