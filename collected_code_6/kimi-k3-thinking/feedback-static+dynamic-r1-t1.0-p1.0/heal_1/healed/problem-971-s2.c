#include <stdio.h>
#include <stdlib.h>

int max_segments(int n, int a, int b, int c)
{
    if (n < 0 || a <= 0 || b <= 0 || c <= 0)
    {
        return -1;
    }

    int *dp = (int *)malloc(((size_t)n + 1u) * sizeof(int));
    if (dp == NULL)
    {
        return -1;
    }

    dp[0] = 0;

    for (int i = 1; i <= n; i++)
    {
        int candidate_a = (i >= a) ? dp[i - a] : -1;
        int candidate_b = (i >= b) ? dp[i - b] : -1;
        int candidate_c = (i >= c) ? dp[i - c] : -1;

        int best = candidate_a;

        if (candidate_b > best)
        {
            best = candidate_b;
        }
        if (candidate_c > best)
        {
            best = candidate_c;
        }

        dp[i] = (best >= 0) ? best + 1 : -1;
    }

    int result = dp[n];

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

    printf("Enter n, a, b and c: ");

    if (scanf("%d %d %d %d", &n, &a, &b, &c) != 4)
    {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (n < 0 || a <= 0 || b <= 0 || c <= 0)
    {
        fprintf(stderr, "Error: n must be non-negative and a, b, c must be positive.\n");
        return EXIT_FAILURE;
    }

    result = max_segments(n, a, b, c);

    if (result < 0)
    {
        printf("No valid segmentation possible.\n");
    }
    else
    {
        printf("Maximum number of segments: %d\n", result);
    }

    return EXIT_SUCCESS;
}