#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int goldMaxCollection(int goldTable[][10], int n, int m, int memo[10][10], int i, int j) {
    if (i < 0 || i >= n || j < 0 || j >= m) return 0;
    if (memo[i][j] != -1) return memo[i][j];
    int right = goldMaxCollection(goldTable, n, m, memo, i, j + 1);
    int rightUp = goldMaxCollection(goldTable, n, m, memo, i - 1, j + 1);
    int rightDown = goldMaxCollection(goldTable, n, m, memo, i + 1, j + 1);
    /* Possible weaknesses found:
     * ASan: stack-buffer-overflow
     */
    memo[i][j] = goldTable[i][j] + max(right, max(rightUp, rightDown));
    return memo[i][j];
}

/* Possible weaknesses found:
 *  expected 'int (*)[10]' but argument is of type 'int (*)[4]'
 */
int solveGoldMineProblem(int goldTable[][10], int n, int m) {
    int memo[10][10];
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            memo[i][j] = -1;
        }
    }
    int res = 0;
    for (int i = 0; i < n; ++i) {
        res = max(res, goldMaxCollection(goldTable, n, m, memo, i, 0));
    }
    return res;
}

int main() {
    int m = 4, n = 4;
    int goldTable[4][4] = {{1, 3, 1, 5}, {2, 2, 4, 1}, {5, 0, 2, 3}, {0, 6, 1, 2}};
    /* Possible weaknesses found:
     *  passing argument 1 of 'solveGoldMineProblem' from incompatible pointer type [-Wincompatible-pointer-types]
     */
    printf("%d", solveGoldMineProblem(goldTable, n, m));
    return 0;
}