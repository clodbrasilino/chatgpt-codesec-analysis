#include <stdio.h>
#include <stdlib.h>

int max_segments(int n, int a, int b, int c)
{
    int *dp;
    int result;
    /* Possible weaknesses found:
     *  The scope of the variable 'best' can be reduced. [variableScope]
     */
    int best;
    int i;

    if (n < 0 || a <= 0 || b <= 0 || c <= 0)
    {
        return -1;
    }

    dp = malloc(((size_t)n + 1U) * sizeof(int));
    if (dp == NULL)
    {
        return -1;
    }

    dp[0] = 0;
    for (i = 1; i <= n; i++)
    {
        dp[i] = -1;
    }

    for (i = 1; i <= n; i++)
    {
        /* Possible weaknesses found:
         *  Assignment 'best=-1', assigned value is -1
         */
        best = -1;
        /* Possible weaknesses found:
         *  Condition 'dp[i-a]+1>best' is always true
         *  Condition 'dp[i-a]+1>best' is always true [knownConditionTrueFalse]
         *  Assuming that condition 'dp[i-a]>=0' is not redundant
         */
        if (i >= a && dp[i - a] >= 0 && dp[i - a] + 1 > best)
        {
            best = dp[i - a] + 1;
        }
        if (i >= b && dp[i - b] >= 0 && dp[i - b] + 1 > best)
        {
            best = dp[i - b] + 1;
        }
        if (i >= c && dp[i - c] >= 0 && dp[i - c] + 1 > best)
        {
            best = dp[i - c] + 1;
        }
        dp[i] = best;
    }

    result = dp[n];
    free(dp);
    dp = NULL;

    return result;
}

int main(void)
{
    int n;
    int a;
    int b;
    int c;
    int result;

    if (scanf("%d %d %d %d", &n, &a, &b, &c) != 4)
    {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    result = max_segments(n, a, b, c);

    if (result >= 0)
    {
        printf("%d\n", result);
    }
    else
    {
        printf("-1\n");
    }

    return EXIT_SUCCESS;
}