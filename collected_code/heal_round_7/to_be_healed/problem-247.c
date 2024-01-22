#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int longestPalindromicSubsequence(const char* str) {
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int n = str ? strlen(str) : 0;
    if(n == 0) {
        return 0;
    }

    int i, j, cl;
    int **L = (int **)calloc(n, sizeof(int *));
    if(L == NULL) {
        return 0;
    }

    for (i = 0; i < n; i++) {
        L[i] = (int *)calloc(n, sizeof(int));
        if(L[i] == NULL) {
            while(i > 0){
                free(L[--i]);
            }
            free(L);
            return 0;
        }
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

    int res = L[0][n - 1];
    for(i=0; i<n; i++) {
        free(L[i]);
    }
    free(L);

    return res;
}

int main() {
    char str[] = "ABCBDEFGCDCFEDGHIJKL";
    int length = longestPalindromicSubsequence(str);
    printf("The length of the longest palindromic subsequence is %d\n", length);
    return 0;
}