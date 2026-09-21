#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max3(int a, int b, int c) {
    if (a >= b && a >= c) return a;
    if (b >= a && b >= c) return b;
    return c;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 5, got <no output>
  *  test case 2 failed: expected 3, got <no output>
  *  test case 0 failed: expected 2, got <no output>
  */

int lcsOfThree(const char* X, const char* Y, const char* Z, int m, int n, int o) {
    int*** L = (int***)malloc((m + 1) * sizeof(int**));
    if (!L) return -1;

    for (int i = 0; i <= m; i++) {
        L[i] = (int**)malloc((n + 1) * sizeof(int*));
        if (!L[i]) {
            for (int k = 0; k < i; k++) {
                for (int j = 0; j <= n; j++) free(L[k][j]);
                free(L[k]);
            }
            free(L);
            return -1;
        }
        for (int j = 0; j <= n; j++) {
            L[i][j] = (int*)malloc((o + 1) * sizeof(int));
            if (!L[i][j]) {
                for (int k = 0; k < j; k++) free(L[i][k]);
                free(L[i]);
                for (int k = 0; k < i; k++) {
                    for (int l = 0; l <= n; l++) free(L[k][l]);
                    free(L[k]);
                }
                free(L);
                return -1;
            }
        }
    }

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= o; k++) {
                if (i == 0 || j == 0 || k == 0) {
                    L[i][j][k] = 0;
                } else if (X[i - 1] == Y[j - 1] && X[i - 1] == Z[k - 1]) {
                    L[i][j][k] = L[i - 1][j - 1][k - 1] + 1;
                } else {
                    L[i][j][k] = max3(L[i - 1][j][k], L[i][j - 1][k], L[i][j][k - 1]);
                }
            }
        }
    }

    int result = L[m][n][o];

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            free(L[i][j]);
        }
        free(L[i]);
    }
    free(L);

    return result;
}

int main(void) {
    const char* X = "AGGT12";
    const char* Y = "12TXAYB";
    const char* Z = "12XBA";

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int m = strlen(X);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int n = strlen(Y);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int o = strlen(Z);

    int lcs_length = lcsOfThree(X, Y, Z, m, n, o);

    if (lcs_length != -1) {
        printf("Length of LCS is %d\n", lcs_length);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}