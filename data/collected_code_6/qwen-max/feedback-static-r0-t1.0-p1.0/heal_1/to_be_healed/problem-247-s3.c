#include <stdio.h>
#include <string.h>

/* Possible weaknesses found:
 *  Parameter 'X' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'Y' can be declared as pointer to const [constParameterPointer]
 */
int lcs(char *X, char *Y, int m, int n) {
    int L[m + 1][n + 1];
    int i, j;

    for (i = 0; i <= m; i++) {
        for (j = 0; j <= n; j++) {
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

int longestPalSubseq(char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int n = strlen(str);
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char revStr[n + 1];
    int i;

    for (i = 0; i < n; i++)
        revStr[i] = str[n - 1 - i];
    revStr[i] = '\0';

    return lcs(str, revStr, n, n);
}

int main() {
    char str[] = "agbdba";
    printf("The length of the longest palindromic subsequence is %d\n", longestPalSubseq(str));
    return 0;
}