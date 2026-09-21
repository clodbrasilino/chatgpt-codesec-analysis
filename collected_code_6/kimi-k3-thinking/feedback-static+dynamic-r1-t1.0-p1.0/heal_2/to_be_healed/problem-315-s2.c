#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[512];
    size_t newlinePos;
    int result;
    int ch;

    printf("Enter a sentence: ");

    if (fgets(str, sizeof(str), stdin) == NULL)
    {
        fprintf(stderr, "Error: failed to read input.\n");
        return 1;
    }

    newlinePos = strcspn(str, "\n");
    if (str[newlinePos] == '\n')
    {
        str[newlinePos] = '\0';
    }
    else if (!feof(stdin))
    {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }
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