#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int max(int a, int b) {
    return (a > b) ? a : b;
}

int gold_mine(int gold[MAX][MAX], int m, int n) {
    int dp[MAX][MAX];
    for (int col = n - 1; col >= 0; col--) {
        for (int row = 0; row < m; row++) {
            int right_up = (row == 0 || col == n - 1) ? 0 : dp[row - 1][col + 1];
            int right = (col == n - 1) ? 0 : dp[row][col + 1];
            int right_down = (row == m - 1 || col == n - 1) ? 0 : dp[row + 1][col + 1];

            dp[row][col] = gold[row][col] + max(max(right_up, right), right_down);
        }
    }

    int max_gold = 0;
    for (int i = 0; i < m; i++) {
        if (dp[i][0] > max_gold) {
            max_gold = dp[i][0];
        }
    }
    return max_gold;
}

int main() {
    int m, n;
    if (scanf("%d %d", &m, &n) != 2 || m <= 0 || m > MAX || n <= 0 || n > MAX) {
        printf("Invalid input\n");
        return 1;
    }

    int gold[MAX][MAX];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%d", &gold[i][j]) != 1) {
                printf("Invalid input\n");
                return 1;
            }
        }
    }

    int result = gold_mine(gold, m, n);
    printf("%d\n", result);
    return 0;
}