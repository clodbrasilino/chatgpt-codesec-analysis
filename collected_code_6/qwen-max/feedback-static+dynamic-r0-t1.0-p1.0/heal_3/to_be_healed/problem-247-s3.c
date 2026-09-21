#include <stdio.h>
#include <string.h>

int lcs(const char *X, const char *Y, int m, int n) {
    int L[m + 1][n + 1];
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = (L[i - 1][j] > L[i][j - 1]) ? L[i - 1][j] : L[i][j - 1];
        }
    }
    return L[m][n];
}

int longestPalSubseq(const char *str, size_t n) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char revStr[n + 1];
    for (size_t i = 0; i < n; i++)
        revStr[n - 1 - i] = str[i];
    revStr[n] = '\0';

    return lcs(str, revStr, n, n);
}

int main() {
    const char str[] = "agbdba";
    size_t n = sizeof(str) / sizeof(str[0]) - 1;
    printf("The length of the longest palindromic subsequence is %d\n", longestPalSubseq(str, n));
    return 0;
}