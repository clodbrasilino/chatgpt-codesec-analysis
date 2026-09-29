#include <stdio.h>
#include <stdlib.h>

#define MAX_M 50

int countSequences(int m, int n) {
    int dp[MAX_M][MAX_M], x, v, j;

    for (x = 0; x < m; x++) {
        for (v = 0; v < m; v++) {
            dp[x][v] = 0;
        }
    }

    for (x = 0; x < m; x++) {
        dp[0][x] = 1;
    }

    for (x = 1; x < m; x++) {
        for (v = 1; v < n; v++) {
            dp[x][v] = dp[x - 1][v] + dp[x / 2][v - 1];
        }
    }

    int count = 0;
    for (j = 0; j < m; j++) {
        count += dp[j][n - 1];
    }

    return count;
}

int main() {
    int m, n;
    printf("Enter the value of m: ");
    scanf("%d", &m);
    printf("Enter the value of n: ");
    scanf("%d", &n);

    if (m >= 1 && m <= 50 && n >= 1 && n <= 50) {
        int count = countSequences(m, n);
        printf("The number of sequences is: %d\n", count);
    }
    else {
        printf("Invalid input! Please ensure 1 <= m,n <= 50\n");
        return 1;
    }

    return 0;
}