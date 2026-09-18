#include <stdio.h>
#include <string.h>

#define MAX(a, b) ((a) > (b)) ? (a) : (b)

int goldMine(int gold[][3], int m, int n){
    int goldTable[m][n];

    memset(goldTable, 0, sizeof(goldTable));

    for (int col = n-1; col >= 0; col--) {
        for (int row = 0; row < m; row++) {
            int right = (col == n-1) ? 0 : goldTable[row][col + 1];
            int right_up = (row == 0 || col == n-1) ? 0 : goldTable[row - 1][col + 1];
            int right_down = (row == m - 1 || col == n - 1) ? 0 : goldTable[row + 1][col + 1];

            goldTable[row][col] = gold[row][col] + MAX(right, MAX(right_up, right_down));
        }
    }
    int res = goldTable[0][0];
    for (int i = 1; i < m; i++)
        res = MAX(res, goldTable[i][0]);
    return res;
}

int main() {
   int gold[][3] = {{1, 3, 1}, {3, 3, 1}, {3, 1, 2}};
   int m = 3, n = 3;
   printf("The maximum amount of gold is %d", goldMine(gold, m, n));
   return 0;
}