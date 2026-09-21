#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFFER_SIZE 1001

int minSwaps(const char *s1, const char *s2)
{
    size_t len1, len2, i;
    int count0_s1 = 0, count1_s1 = 0;
    int count0_s2 = 0, count1_s2 = 0;
    int mismatch0 = 0, mismatch1 = 0;

    if (s1 == NULL || s2 == NULL)
        return -1;

    len1 = strnlen(s1, BUFFER_SIZE);
    len2 = strnlen(s2, BUFFER_SIZE);

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

int readBinaryString(char *buffer, size_t size)
{
    size_t len;

    if (buffer == NULL || size == 0)
        return 0;

    if (fgets(buffer, size, stdin) == NULL)
        return 0;

    len = strnlen(buffer, size);

    if (len == size - 1 && buffer[len - 1] != '\n')
    {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF)
            ;
        buffer[0] = '\0';
        return 0;
    }

    len = strcspn(buffer, "\n");
    if (len > 0 && buffer[len - 1] == '\r')
        len--;
    buffer[len] = '\0';

    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char s1[BUFFER_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char s2[BUFFER_SIZE];
    int result;

    printf("Enter first binary string: ");
    if (!readBinaryString(s1, sizeof(s1)))
    {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    printf("Enter second binary string: ");
    if (!readBinaryString(s2, sizeof(s2)))
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