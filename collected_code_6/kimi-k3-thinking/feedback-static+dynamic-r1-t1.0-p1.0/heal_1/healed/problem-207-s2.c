#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_INPUT_LEN 4096

static int max_int(int a, int b)
{
    return (a > b) ? a : b;
}

static size_t bounded_strnlen(const char *str, size_t max_len)
{
    size_t len = 0;

    while (len < max_len && str[len] != '\0')
    {
        len++;
    }

    return len;
}

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

    n = bounded_strnlen(str, MAX_INPUT_LEN + 1);

    if (n > MAX_INPUT_LEN)
    {
        return -1;
    }

    if (n == 0)
    {
        return 0;
    }

    if ((n + 1) > SIZE_MAX / (n + 1))
    {
        return -1;
    }

    if ((n + 1) * (n + 1) > SIZE_MAX / sizeof(*dp))
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
    const char *tests[] = { "AABEBCDD", "aabb", "aa" };
    size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    size_t k;

    for (k = 0; k < num_tests; k++)
    {
        int result = longestRepeatingSubsequence(tests[k]);

        if (result < 0)
        {
            fprintf(stderr, "Error: failed to compute longest repeating subsequence\n");
            return EXIT_FAILURE;
        }

        printf("%d\n", result);
    }

    return EXIT_SUCCESS;
}