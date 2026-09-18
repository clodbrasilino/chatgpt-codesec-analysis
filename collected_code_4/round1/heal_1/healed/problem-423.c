#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int solveGoldMine(int **gold, int m, int n) {
    int i, j;

    int **dp = (int **)malloc(m * sizeof(int *));
    if (dp == NULL)
        return -1;

    for (i = 0; i < m; i++) {
        dp[i] = (int *)malloc(n * sizeof(int));
        if (dp[i] == NULL) {
            for (int k=0; k<i; k++)
                free(dp[k]);
            free(dp);
            return -1;
        }
        dp[i][n - 1] = gold[i][n - 1];
    }

    for (j = n - 2; j >= 0; j--) {
        for (i = 0; i < m; i++) {
            int right = dp[i][j + 1];
            int right_up = (i == 0) ? 0 : dp[i - 1][j + 1];
            int right_down = (i == m - 1) ? 0 : dp[i + 1][j + 1];
            dp[i][j] = gold[i][j] + MAX(right, MAX(right_up, right_down));
        }
    }

    int result = dp[0][0];
    for (i = 1; i < m; i++)
        result = MAX(result, dp[i][0]);

    for (i = 0; i < m; i++)
        free(dp[i]);
    free(dp);

    return result;
}

int main() {
    int r, c, i, j;

    printf("Enter number of rows and columns in the mine: ");
    scanf("%d %d", &r, &c);

    int **goldmine = (int **)malloc(r * sizeof(int *));
    if (goldmine == NULL)
        return -1;

    for(i = 0; i < r; i++) {
        goldmine[i] = (int *)malloc(c * sizeof(int));
        if (goldmine[i] == NULL) {
            for (int k = 0; k < i; k++)
                free(goldmine[k]);
            free(goldmine);
            return -1;
        }
    }

    printf("Enter %d elements of the gold mine:\n", r * c);
    for(i = 0; i < r; i++)
        for(j = 0; j < c; j++)
            scanf("%d", &(goldmine[i][j]));

    printf("Maximum gold that can be collected is: %d\n", solveGoldMine(goldmine, r, c));

    for(i = 0; i < r; i++)
        free(goldmine[i]);
    free(goldmine);

    return 0;
}