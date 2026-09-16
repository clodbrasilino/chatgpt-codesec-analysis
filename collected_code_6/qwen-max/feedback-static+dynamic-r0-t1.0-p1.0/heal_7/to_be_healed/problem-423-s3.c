#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 70, got <no output>
  *  test case 2 failed: expected 13, got <no output>
  *  test case 0 failed: expected 16, got <no output>
  */

/* Possible weaknesses found:
 *  expected 'int (*)[4]' but argument is of type 'int (*)[3]'
 */
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

    int gold1[3][3] = { {1, 3, 1},
                        {2, 2, 4},
                        {5, 0, 2} };
    int m1 = 3, n1 = 3;
    /* Possible weaknesses found:
     *  passing argument 1 of 'maxGold' from incompatible pointer type [-Wincompatible-pointer-types]
     */
    printf("%d\n", maxGold(gold1, m1, n1));

    int gold2[2][3] = { {1, 3, 1},
                        {15, 2, 4} };
    int m2 = 2, n2 = 3;
    /* Possible weaknesses found:
     *  passing argument 1 of 'maxGold' from incompatible pointer type [-Wincompatible-pointer-types]
     */
    printf("%d\n", maxGold(gold2, m2, n2));

    return 0;
}