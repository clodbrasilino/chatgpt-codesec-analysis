#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int max_value(int a, int b)
{
    return (a > b) ? a : b;
}

int longest_repeating_subsequence(const char *str)
{
    size_t n;
    size_t dim;
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

    dim = n + 1;

    if (dim > SIZE_MAX / dim)
    {
        return -1;
    }

    if (dim * dim > SIZE_MAX / sizeof(int))
    {
        return -1;
    }

    dp = (int *)calloc(dim * dim, sizeof(int));
    if (dp == NULL)
    {
        return -1;
    }

    for (i = 1; i < dim; i++)
    {
        for (j = 1; j < dim; j++)
        {
            if (str[i - 1] == str[j - 1] && i != j)
            {
                dp[i * dim + j] = 1 + dp[(i - 1) * dim + (j - 1)];
            }
            else
            {
                dp[i * dim + j] = max_value(dp[(i - 1) * dim + j],
                                            dp[i * dim + (j - 1)]);
            }
        }
    }

    result = dp[n * dim + n];
    free(dp);
    dp = NULL;

    return result;
}

int main(void)
{
    const char *tests[] = {
        "AABEBCDD",
        "AAB",
        "ABC",
        "ATA",
        "AAAA",
        ""
    };
    size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    size_t k;
    int length;

    for (k = 0; k < num_tests; k++)
    {
        length = longest_repeating_subsequence(tests[k]);
        if (length < 0)
        {
            fprintf(stderr, "Error: failed to process input string\n");
            return EXIT_FAILURE;
        }
        printf("Input: \"%s\" -> Longest repeating subsequence length: %d\n",
               tests[k], length);
    }

    return EXIT_SUCCESS;
}