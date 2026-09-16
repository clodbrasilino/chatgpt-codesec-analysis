#include <stdio.h>
#include <stdlib.h>

int maxGold(int gold[][4], int m, int n) {
    int dp[100][100] = {0};
    int result = 0;

    for (int col = n-1; col >= 0; --col) {
        for (int row = 0; row < m; ++row) {
            int right = (col == n-1) ? 0 : dp[row][col+1];
            int right_up = (row == 0 || col == n-1) ? 0 : dp[row-1][col+1];
            int right_down = (row == m-1 || col == n-1) ? 0 : dp[row+1][col+1];

            dp[row][col] = gold[row][col] + (right > right_up ? (right > right_down ? right : right_down) : (right_up > right_down ? right_up : right_down));
            if (col == 0 && (result < dp[row][col])) {
                result = dp[row][col];
            }
        }
    }
    return result;
}

int main() {
    int gold0[4][4] = { {1, 3, 1, 5},
                        {2, 2, 4, 1},
                        {5, 0, 2, 3},
                        {0, 6, 1, 2} };
    int m0 = 4, n0 = 4;
    printf("%d\n", maxGold(gold0, m0, n0));

    int gold1[3][4] = { {1, 3, 1, 0},
                        {2, 2, 4, 0},
                        {5, 0, 2, 0} };
    int m1 = 3, n1 = 3;
    printf("%d\n", maxGold(gold1, m1, n1));

    int gold2[2][4] = { {1, 3, 1, 0},
                        {15, 2, 4, 0} };
    int m2 = 2, n2 = 3;
    printf("%d\n", maxGold(gold2, m2, n2));

    return 0;
}