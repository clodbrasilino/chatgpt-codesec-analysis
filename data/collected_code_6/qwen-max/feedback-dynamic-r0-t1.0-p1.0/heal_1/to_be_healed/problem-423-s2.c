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

            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 796091951 + 1735866207 cannot be represented in type 'int' (AFL crash: id:000003,sig:06,src:000000,time:35854,execs:5938,op:havoc,rep:13)
             */
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
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:253,execs:135,op:havoc,rep:9; likely memory-safety defect
  */

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    int gold[MAX][MAX];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &gold[i][j]);
        }
    }

    int result = gold_mine(gold, m, n);
    printf("%d\n", result);
    return 0;
}