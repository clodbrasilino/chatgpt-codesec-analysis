#include <stdio.h>
#include <string.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int longestPalindromicSubsequence(char* str) {
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int n = strlen(str);
    int i, j, cl;
    int L[n][n];

    for (i = 0; i < n; i++) {
        L[i][i] = 1;
    }

    for (cl = 2; cl <= n; cl++) {
        for (i = 0; i < n - cl + 1; i++) {
            j = i + cl - 1;
            if (str[i] == str[j] && cl == 2) {
                L[i][j] = 2;
            } else if (str[i] == str[j]) {
                L[i][j] = L[i + 1][j - 1] + 2;
            } else {
                L[i][j] = max(L[i][j - 1], L[i + 1][j]);
            }
        }
    }

    return L[0][n - 1];
}

int main() {
    char str[] = "ABCBDEFGCDCFEDGHIJKL";
    int length = longestPalindromicSubsequence(str);
    printf("The length of the longest palindromic subsequence is %d\n", length);
    return 0;
}