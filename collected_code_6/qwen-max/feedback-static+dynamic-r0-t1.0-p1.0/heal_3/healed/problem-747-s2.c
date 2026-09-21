#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lcsLength(const char* X, int m, const char* Y, int n, const char* Z, int o) {
    int L[m+1][n+1][o+1];
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= o; k++) {
                if (i == 0 || j == 0 || k == 0)
                    L[i][j][k] = 0;
                else if (X[i-1] == Y[j-1] && X[i-1] == Z[k-1])
                    L[i][j][k] = L[i-1][j-1][k-1] + 1;
                else
                    L[i][j][k] = (L[i-1][j][k] > L[i][j-1][k]) ? ((L[i-1][j][k] > L[i][j][k-1]) ? L[i-1][j][k] : L[i][j][k-1]) : ((L[i][j-1][k] > L[i][j][k-1]) ? L[i][j-1][k] : L[i][j][k-1]);
            }
        }
    }
    return L[m][n][o];
}

void printLCS(char** buf, int idx, const char* X, const char* Y, const char* Z, int m, int n, int o, int lcsLen, int i, int j, int k, int L[m+1][n+1][o+1]) {
    if (i == 0 || j == 0 || k == 0) return;
    if (X[i-1] == Y[j-1] && X[i-1] == Z[k-1]) {
        (*buf)[idx] = X[i-1];
        printLCS(buf, idx-1, X, Y, Z, m, n, o, lcsLen, i-1, j-1, k-1, L);
    } else if (lcsLen == L[i-1][j][k])
        printLCS(buf, idx, X, Y, Z, m, n, o, lcsLen, i-1, j, k, L);
    else if (lcsLen == L[i][j-1][k])
        printLCS(buf, idx, X, Y, Z, m, n, o, lcsLen, i, j-1, k, L);
    else
        printLCS(buf, idx, X, Y, Z, m, n, o, lcsLen, i, j, k-1, L);
}

int main() {
    const char *X = "AGGT12";
    const char *Y = "12TXAYB";
    const char *Z = "12XBA";
    int m = strlen(X), n = strlen(Y), o = strlen(Z);

    int lcsLen = lcsLength(X, m, Y, n, Z, o);

    int L[m+1][n+1][o+1];
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= o; k++) {
                L[i][j][k] = 0;
            }
        }
    }

    char *lcsBuf = (char*)malloc((lcsLen + 1) * sizeof(char));
    if (lcsBuf == NULL) {
        return -1;
    }
    lcsBuf[lcsLen] = '\0';
    printLCS(&lcsBuf, lcsLen-1, X, Y, Z, m, n, o, lcsLen, m, n, o, L);

    printf("LCS: %s\n", lcsBuf);

    free(lcsBuf);
    return 0;
}