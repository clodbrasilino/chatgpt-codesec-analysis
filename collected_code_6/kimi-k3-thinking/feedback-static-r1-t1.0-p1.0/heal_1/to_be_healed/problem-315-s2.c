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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[512];
    size_t len;
    int result;

    printf("Enter a sentence: ");

    if (fgets(str, sizeof(str), stdin) == NULL)
    {
        fprintf(stderr, "Error: failed to read input.\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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