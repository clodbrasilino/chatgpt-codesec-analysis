#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

#define MAX 100

int max(int a, int b) {
    return (a > b) ? a : b;
}

int64_t gold_mine(int64_t gold[MAX][MAX], int m, int n) {
    int64_t dp[MAX][MAX];
    for (int col = n - 1; col >= 0; col--) {
        for (int row = 0; row < m; row++) {
            int64_t right_up = (row == 0 || col == n - 1) ? 0 : dp[row - 1][col + 1];
            int64_t right = (col == n - 1) ? 0 : dp[row][col + 1];
            int64_t right_down = (row == m - 1 || col == n - 1) ? 0 : dp[row + 1][col + 1];

            int64_t current_gold = gold[row][col] + max(max(right_up, right), right_down);
            if (current_gold < INT64_MIN || current_gold > INT64_MAX) {
                return -1;
            }
            dp[row][col] = current_gold;
        }
    }

    int64_t max_gold = 0;
    for (int i = 0; i < m; i++) {
        if (dp[i][0] > max_gold) {
            max_gold = dp[i][0];
        }
    }
    return max_gold;
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    if (m <= 0 || n <= 0 || m > MAX || n > MAX) {
        printf("-1\n");
        return 1;
    }

    int64_t gold[MAX][MAX];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%ld", &gold[i][j]);
        }
    }

    int64_t result = gold_mine(gold, m, n);
    printf("%ld\n", result);
    return 0;
}