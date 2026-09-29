#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

bool areRotations(const char *str1, const char *str2)
{
    if (str1 == NULL || str2 == NULL)
    {
        return false;
    }

    size_t len1 = strnlen(str1, SIZE_MAX);
    size_t len2 = strnlen(str2, SIZE_MAX);

    if (len1 != len2 || len1 == 0)
    {
        return false;
    }

    if (len1 > (SIZE_MAX - 1) / 2)
    {
        return false;
    }

    size_t concatLen = len1 * 2 + 1;
    char *concat = (char *)malloc(concatLen);
    if (concat == NULL)
    {
        return false;
    }

    size_t remaining = concatLen;
    size_t copySize = (len1 < remaining - 1) ? len1 : remaining - 1;
    memcpy(concat, str1, copySize);
    remaining -= copySize;

    copySize = (len1 < remaining - 1) ? len1 : remaining - 1;
    memcpy(concat + len1, str1, copySize);
    remaining -= copySize;

    concat[concatLen - 1] = '\0';

    bool result = (strstr(concat, str2) != NULL);

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
        printf("true\n");
    }
    else
    {
        printf("false\n");
    }

    return 0;
}