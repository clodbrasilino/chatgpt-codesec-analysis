#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int max(const int a, const int b) {
    return (a > b) ? a : b;
}

int longestCommonSubsequence(const char* X, const char* Y, const char* Z, const int m, const int n, const int o) {
    int L[m+1][n+1][o+1];
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= o; k++) {
                if (i == 0 || j == 0 || k == 0)
                    L[i][j][k] = 0;
                else if (X[i-1] == Y[j-1] && X[i-1] == Z[k-1])
                    L[i][j][k] = L[i-1][j-1][k-1] + 1;
                else
                    L[i][j][k] = max(max(L[i-1][j][k], L[i][j-1][k]), L[i][j][k-1]);
            }
        }
    }
    return L[m][n][o];
}

int main() {
    const char X[] = "AGGT12";
    const char Y[] = "12TXAYB";
    const char Z[] = "12XBA";

    const int m = sizeof(X) / sizeof(X[0]) - 1;
    const int n = sizeof(Y) / sizeof(Y[0]) - 1;
    const int o = sizeof(Z) / sizeof(Z[0]) - 1;

    printf("Length of LCS is %d\n", longestCommonSubsequence(X, Y, Z, m, n, o));
    return 0;
}