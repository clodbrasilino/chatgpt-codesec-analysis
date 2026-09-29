#include <stdio.h>
#include <stdlib.h>

#define MAX_ROWS 10000
#define MAX_COLS 10000

static int max_of_three(int a, int b, int c)
{
    int m = a;
    if (b > m)
    {
        m = b;
    }
    if (c > m)
    {
        m = c;
    }
    return m;
}

static int validate_mine(const int *mine, int rows, int cols)
{
    int i;
    int j;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if (mine[i * cols + j] < 0)
            {
                return -1;
            }
        }
    }
    return 0;
}

int gold_mine_collect(const int *mine, int rows, int cols, int *max_gold)
{
    int *prev = NULL;
    int *curr = NULL;
    int *tmp = NULL;
    int i;
    int j;
    int best;

    if (mine == NULL || max_gold == NULL)
    {
        return -1;
    }
    if (rows <= 0 || cols <= 0 || rows > MAX_ROWS || cols > MAX_COLS)
    {
        return -1;
    }
    if (validate_mine(mine, rows, cols) != 0)
    {
        return -1;
    }

    prev = (int *)malloc((size_t)rows * sizeof(int));
    if (prev == NULL)
    {
        return -1;
    }
    curr = (int *)malloc((size_t)rows * sizeof(int));
    if (curr == NULL)
    {
        free(prev);
        prev = NULL;
        return -1;
    }

    for (i = 0; i < rows; i++)
    {
        prev[i] = mine[i * cols];
    }

    for (j = 1; j < cols; j++)
    {
        for (i = 0; i < rows; i++)
        {
            int up = (i > 0) ? prev[i - 1] : 0;
            int same = prev[i];
            int down = (i < rows - 1) ? prev[i + 1] : 0;
            curr[i] = mine[i * cols + j] + max_of_three(up, same, down);
        }
        tmp = prev;
        prev = curr;
        curr = tmp;
    }

    best = prev[0];
    for (i = 1; i < rows; i++)
    {
        if (prev[i] > best)
        {
            best = prev[i];
        }
    }

    free(prev);
    prev = NULL;
    free(curr);
    curr = NULL;

    *max_gold = best;
    return 0;
}

int main(void)
{
    const int rows = 4;
    const int cols = 4;
    int mine[4][4] = {
        {1, 3, 1, 5},
        {2, 2, 4, 1},
        {5, 0, 2, 3},
        {0, 6, 1, 2}
    };
    int max_gold = 0;

    if (gold_mine_collect(&mine[0][0], rows, cols, &max_gold) != 0)
    {
        fprintf(stderr, "Error: invalid input or allocation failure\n");
        return EXIT_FAILURE;
    }

    printf("Maximum gold collected: %d\n", max_gold);
    return EXIT_SUCCESS;
}