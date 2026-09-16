#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int max_int(int a, int b)
{
    return (a > b) ? a : b;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 3, got <no output>
  *  test case 1 failed: expected 2, got <no output>
  *  test case 2 failed: expected 1, got <no output>
  */

int longestRepeatingSubsequence(const char *str)
{
    size_t n;
    size_t i;
    size_t j;
    int *dp;
    int result;

    if (str == NULL)
    {
        return -1;
    }

    n = strlen(str);

    if (n == 0)
    {
        return 0;
    }

    if ((n + 1) > SIZE_MAX / (n + 1))
    {
        return -1;
    }

    dp = calloc((n + 1) * (n + 1), sizeof(*dp));
    if (dp == NULL)
    {
        return -1;
    }

    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (str[i - 1] == str[j - 1] && i != j)
            {
                dp[i * (n + 1) + j] = dp[(i - 1) * (n + 1) + (j - 1)] + 1;
            }
            else
            {
                dp[i * (n + 1) + j] = max_int(dp[(i - 1) * (n + 1) + j],
                                              dp[i * (n + 1) + (j - 1)]);
            }
        }
    }

    result = dp[n * (n + 1) + n];

    free(dp);
    dp = NULL;

    return result;
}

int main(void)
{
    const char *str = "AABEBCDD";
    int result;

    result = longestRepeatingSubsequence(str);

    if (result < 0)
    {
        fprintf(stderr, "Error: failed to compute longest repeating subsequence\n");
        return EXIT_FAILURE;
    }

    printf("Longest repeating subsequence length: %d\n", result);

    return EXIT_SUCCESS;
}