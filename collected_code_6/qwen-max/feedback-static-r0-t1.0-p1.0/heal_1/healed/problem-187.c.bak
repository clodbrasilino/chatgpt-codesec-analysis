#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int max(const int a, const int b) {
    return (a > b) ? a : b;
}

char* longestCommonSubsequence(const char *X, const char *Y, const int m, const int n) {
    int L[m + 1][n + 1];
    int i, j;

    for (i = 0; i <= m; i++) {
        for (j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }

    int index = L[m][n];
    char *lcs = (char *)malloc((index + 1) * sizeof(char));
    lcs[index] = '\0';

    i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[index - 1] = X[i - 1];
            i--;
            j--;
            index--;
        } else if (L[i - 1][j] > L[i][j - 1])
            i--;
        else
            j--;
    }

    return lcs;
}

int main() {
    const char X[] = "AGGTAB";
    const char Y[] = "GXTXAYB";
    const int m = strlen(X);
    const int n = strlen(Y);

    char *lcs = longestCommonSubsequence(X, Y, m, n);
    printf("Longest Common Subsequence: %s\n", lcs);
    free(lcs);

    return 0;
}