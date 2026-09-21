#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

#define MAX_INPUT_LENGTH 4096

static int bounded_string_length(const char *str, size_t max_length, size_t *out_length)
{
    const char *terminator;

    if (str == NULL || out_length == NULL || max_length == SIZE_MAX)
    {
        return -1;
    }

    terminator = (const char *)memchr(str, '\0', max_length + 1);
    if (terminator == NULL)
    {
        return -1;
    }

    *out_length = (size_t)(terminator - str);
    return 0;
}

static int shortest_common_supersequence_length(const char *str1, const char *str2)
{
    size_t len1;
    size_t len2;
    size_t i;
    size_t j;
    size_t cols;
    size_t cells;
    int *dp;
    int result;

    if (str1 == NULL || str2 == NULL)
    {
        return -1;
    }

    if (bounded_string_length(str1, MAX_INPUT_LENGTH, &len1) != 0)
    {
        return -1;
    }

    if (bounded_string_length(str2, MAX_INPUT_LENGTH, &len2) != 0)
    {
        return -1;
    }

    if (len1 == SIZE_MAX || len2 == SIZE_MAX)
    {
        return -1;
    }
    cols = len2 + 1;

    if (len1 + 1 > SIZE_MAX / cols)
    {
        return -1;
    }
    cells = (len1 + 1) * cols;

    if (cells > SIZE_MAX / sizeof(int))
    {
        return -1;
    }

    if (len2 > (size_t)INT_MAX || len1 > (size_t)INT_MAX - len2)
    {
        return -1;
    }

    dp = (int *)malloc(cells * sizeof(int));
    if (dp == NULL)
    {
        return -1;
    }

    for (i = 0; i <= len1; i++)
    {
        for (j = 0; j <= len2; j++)
        {
            if (i == 0)
            {
                dp[i * cols + j] = (int)j;
            }
            else if (j == 0)
            {
                dp[i * cols + j] = (int)i;
            }
            else if (str1[i - 1] == str2[j - 1])
            {
                dp[i * cols + j] = 1 + dp[(i - 1) * cols + (j - 1)];
            }
            else
            {
                int above = dp[(i - 1) * cols + j];
                int left = dp[i * cols + (j - 1)];
                dp[i * cols + j] = 1 + (above < left ? above : left);
            }
        }
    }

    result = dp[len1 * cols + len2];
    free(dp);
    dp = NULL;

    return result;
}

int main(void)
{
    const char *str1 = "AGGTAB";
    const char *str2 = "GXTXAYB";
    int result;

    result = shortest_common_supersequence_length(str1, str2);
    if (result < 0)
    {
        fprintf(stderr, "Error: invalid input or allocation failure\n");
        return EXIT_FAILURE;
    }

    printf("Length of shortest common supersequence: %d\n", result);

    return EXIT_SUCCESS;
}