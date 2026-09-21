#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int shortest_supersequence_length(const char *str1, const char *str2)
{
    size_t len1;
    size_t len2;
    size_t i;
    size_t j;
    size_t *dp;
    size_t lcs_length;
    size_t result;

    if (str1 == NULL || str2 == NULL)
    {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len1 = strlen(str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len2 = strlen(str2);

    dp = malloc((len2 + 1) * sizeof(*dp));
    if (dp == NULL)
    {
        return -1;
    }

    for (j = 0; j <= len2; j++)
    {
        dp[j] = 0;
    }

    for (i = 1; i <= len1; i++)
    {
        size_t prev_diagonal = 0;
        for (j = 1; j <= len2; j++)
        {
            size_t temp = dp[j];
            if (str1[i - 1] == str2[j - 1])
            {
                dp[j] = prev_diagonal + 1;
            }
            else
            {
                dp[j] = (dp[j - 1] > dp[j]) ? dp[j - 1] : dp[j];
            }
            prev_diagonal = temp;
        }
    }

    lcs_length = dp[len2];
    free(dp);
    dp = NULL;

    result = len1 + len2 - lcs_length;
    if (result > (size_t)INT_MAX)
    {
        return -1;
    }

    return (int)result;
}

int main(void)
{
    const char *str1 = "AGGTAB";
    const char *str2 = "GXTXAYB";
    int result;

    result = shortest_supersequence_length(str1, str2);
    if (result < 0)
    {
        fprintf(stderr, "Error: invalid input or memory allocation failure\n");
        return EXIT_FAILURE;
    }

    printf("str1: %s\n", str1);
    printf("str2: %s\n", str2);
    printf("Length of shortest common supersequence: %d\n", result);

    return EXIT_SUCCESS;
}