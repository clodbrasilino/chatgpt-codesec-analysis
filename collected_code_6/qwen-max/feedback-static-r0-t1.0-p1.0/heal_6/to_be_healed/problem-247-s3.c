#include <stdio.h>
#include <string.h>
#include <stdint.h>

int lcs(const char *X, const char *Y, size_t m, size_t n) {
    int L[m + 1][n + 1];
    for (size_t i = 0; i <= m; i++) {
        for (size_t j = 0; j <= n; j++) {
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

int longestPalSubseq(const char *str, size_t len) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char revStr[len + 1];
    for (size_t i = 0; i < len; i++)
        revStr[i] = str[len - 1 - i];
    revStr[len] = '\0';

    return lcs(str, revStr, len, len);
}

int main() {
    const char str[] = "agbdba";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    /* Possible weaknesses found:
     *  %zu in format string (no. 1) requires 'size_t' but the argument type is 'signed int'. [invalidPrintfArgType_uint]
     */
    printf("The length of the longest palindromic subsequence is %zu\n", longestPalSubseq(str, len));
    return 0;
}