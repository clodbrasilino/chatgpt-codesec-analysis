#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int areRotations(const char *str1, const char *str2)
{
    if (str1 == NULL || str2 == NULL)
    {
        return 0;
    }

    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    if (len1 != len2 || len1 == 0)
    {
        return 0;
    }

    size_t concatLen = len1 * 2 + 1;
    char *concat = (char *)malloc(concatLen);
    if (concat == NULL)
    {
        return 0;
    }

    snprintf(concat, concatLen, "%s%s", str1, str1);

    int result = (strstr(concat, str2) != NULL);

    free(concat);
    concat = NULL;

    return result;
}

int main(void)
{
    const char *str1 = "abcde";
    const char *str2 = "cdeab";

    if (areRotations(str1, str2))
    {
        printf("The strings are rotations of each other.\n");
    }
    else
    {
        printf("The strings are not rotations of each other.\n");
    }

    return 0;
}