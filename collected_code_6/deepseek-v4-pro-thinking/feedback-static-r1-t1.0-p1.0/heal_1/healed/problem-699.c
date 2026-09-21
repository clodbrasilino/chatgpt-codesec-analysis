#include <stdio.h>
#include <stddef.h>

#define MAX_SAFE_STRING_LENGTH 1048576

static size_t bounded_strlen(const char *str, size_t maxlen)
{
    size_t i = 0;
    if (str != NULL) {
        while (i < maxlen && str[i] != '\0') {
            i++;
        }
    }
    return i;
}

int minSwapsToConvert(const char *str1, const char *str2)
{
    if (str1 == NULL || str2 == NULL)
    {
        return -1;
    }

    size_t len1 = bounded_strlen(str1, MAX_SAFE_STRING_LENGTH);
    size_t len2 = bounded_strlen(str2, MAX_SAFE_STRING_LENGTH);

    if (len1 == MAX_SAFE_STRING_LENGTH || len2 == MAX_SAFE_STRING_LENGTH)
    {
        return -1;
    }

    if (len1 != len2)
    {
        return -1;
    }

    int count1 = 0;
    int count2 = 0;
    int mismatches = 0;

    for (size_t i = 0; i < len1; i++)
    {
        if ((str1[i] != '0' && str1[i] != '1') ||
            (str2[i] != '0' && str2[i] != '1'))
        {
            return -1;
        }

        if (str1[i] == '1')
        {
            count1++;
        }

        if (str2[i] == '1')
        {
            count2++;
        }

        if (str1[i] != str2[i])
        {
            mismatches++;
        }
    }

    if (count1 != count2)
    {
        return -1;
    }

    return mismatches / 2;
}

int main(void)
{
    const char *s1 = "1100";
    const char *s2 = "0011";
    int result = minSwapsToConvert(s1, s2);

    if (result >= 0)
    {
        printf("%d\n", result);
    }
    else
    {
        printf("Invalid input\n");
    }

    return 0;
}