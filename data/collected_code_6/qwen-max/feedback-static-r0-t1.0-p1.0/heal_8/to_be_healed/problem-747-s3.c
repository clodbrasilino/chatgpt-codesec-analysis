#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int longestCommonSubsequence(const char* X, const char* Y, const char* Z, size_t m, size_t n, size_t o) {
    int L[m + 1][n + 1][o + 1];

    for (size_t i = 0; i <= m; i++) {
        for (size_t j = 0; j <= n; j++) {
            for (size_t k = 0; k <= o; k++) {
                if (i == 0 || j == 0 || k == 0) {
                    L[i][j][k] = 0;
                } else if (X[i - 1] == Y[j - 1] && X[i - 1] == Z[k - 1]) {
                    L[i][j][k] = L[i - 1][j - 1][k - 1] + 1;
                } else {
                    L[i][j][k] = max(max(L[i - 1][j][k], L[i][j - 1][k]), L[i][j][k - 1]);
                }
            }
        }
    }
    return L[m][n][o];
}

int main() {
    const char X[] = "AGGT12";
    const char Y[] = "12TXAYB";
    const char Z[] = "12XBA";

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t m = strlen(X);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t n = strlen(Y);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t o = strlen(Z);

    /* Possible weaknesses found:
     *  %zu in format string (no. 1) requires 'size_t' but the argument type is 'signed int'. [invalidPrintfArgType_uint]
     */
    printf("Length of LCS is %zu\n", longestCommonSubsequence(X, Y, Z, m, n, o));

    return 0;
}