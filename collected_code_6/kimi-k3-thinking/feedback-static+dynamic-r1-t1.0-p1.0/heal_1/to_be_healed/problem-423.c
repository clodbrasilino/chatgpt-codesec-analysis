#include <stdio.h>
#include <stdlib.h>

static int max_of_three(int a, int b, int c)
{
    int max = a;

    if (b > max)
    {
        max = b;
    }
    if (c > max)
    {
        max = c;
    }

    return max;
}

int collect_max_gold(const int *mine, int rows, int cols)
{
    int **dp;
    int i;
    int j;
    int result;
    int right;
    int right_up;
    int right_down;

    if (mine == NULL || rows <= 0 || cols <= 0)
    {
        return -1;
    }

    dp = (int **)malloc((size_t)rows * sizeof(int *));
    if (dp == NULL)
    {
        return -1;
    }

    for (i = 0; i < rows; i++)
    {
        dp[i] = (int *)malloc((size_t)cols * sizeof(int));
        if (dp[i] == NULL)
        {
            while (i > 0)
            {
                i--;
                free(dp[i]);
                dp[i] = NULL;
            }
            free(dp);
            dp = NULL;
            return -1;
        }
    }

    for (j = cols - 1; j >= 0; j--)
    {
        for (i = 0; i < rows; i++)
        {
            right = (j == cols - 1) ? 0 : dp[i][j + 1];
            right_up = (i == 0 || j == cols - 1) ? 0 : dp[i - 1][j + 1];
            right_down = (i == rows - 1 || j == cols - 1) ? 0 : dp[i + 1][j + 1];
            dp[i][j] = mine[i * cols + j] + max_of_three(right, right_up, right_down);
        }
    }

    result = dp[0][0];
    for (i = 1; i < rows; i++)
    {
        if (dp[i][0] > result)
        {
            result = dp[i][0];
        }
    }

    for (i = 0; i < rows; i++)
    {
        free(dp[i]);
        dp[i] = NULL;
    }
    free(dp);
    dp = NULL;

    return result;
}

int main(void)
{
    /* Possible weaknesses found:
     *  Variable 'mine' can be declared as const array [constVariable]
     */
    int mine[] = {
        1, 3, 1, 5,
        2, 2, 4, 1,
        5, 0, 2, 3,
        0, 6, 1, 2
    };
    int rows = 4;
    int cols = 4;
    int result;

    result = collect_max_gold(mine, rows, cols);
    if (result < 0)
    {
        fprintf(stderr, "Error: failed to compute maximum gold\n");
        return EXIT_FAILURE;
    }

    printf("Maximum gold collected: %d\n", result);

    return EXIT_SUCCESS;
}