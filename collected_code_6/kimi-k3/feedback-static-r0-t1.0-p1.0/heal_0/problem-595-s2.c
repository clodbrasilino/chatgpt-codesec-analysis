#include <stdio.h>
#include <string.h>

int minSwaps(const char *s1, const char *s2)
{
    int len1, len2, i;
    int count0_s1 = 0, count1_s1 = 0;
    int count0_s2 = 0, count1_s2 = 0;
    int mismatch0 = 0, mismatch1 = 0;

    if (s1 == NULL || s2 == NULL)
        return -1;

    len1 = strlen(s1);
    len2 = strlen(s2);

    if (len1 != len2)
        return -1;

    for (i = 0; i < len1; i++)
    {
        if (s1[i] != '0' && s1[i] != '1')
            return -1;
        if (s2[i] != '0' && s2[i] != '1')
            return -1;

        if (s1[i] == '0')
            count0_s1++;
        else
            count1_s1++;

        if (s2[i] == '0')
            count0_s2++;
        else
            count1_s2++;
    }

    if (count0_s1 != count0_s2 || count1_s1 != count1_s2)
        return -1;

    for (i = 0; i < len1; i++)
    {
        if (s1[i] != s2[i])
        {
            if (s1[i] == '0')
                mismatch0++;
            else
                mismatch1++;
        }
    }

    return (mismatch0 + mismatch1) / 2;
}

int main(void)
{
    char s1[1001];
    char s2[1001];
    int result;

    printf("Enter first binary string: ");
    if (scanf("%1000s", s1) != 1)
    {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    printf("Enter second binary string: ");
    if (scanf("%1000s", s2) != 1)
    {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    result = minSwaps(s1, s2);

    if (result == -1)
        printf("Conversion not possible.\n");
    else
        printf("Minimum swaps required: %d\n", result);

    return 0;
}