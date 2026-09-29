#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

char* longestCommonSubsequence(const char *X, const char *Y, int m, int n) {
    int L[m + 1][n + 1];
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
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
    if (lcs == NULL) {
        return NULL;
    }
    lcs[index] = '\0';

    int i = m, j = n;
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

void reverseString(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

int main() {
    const char X[] = "AGGTAB";
    const char Y[] = "GXTXAYB";

    int m = 6;
    int n = 7;

    char *lcs = longestCommonSubsequence(X, Y, m, n);
    if (lcs == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    reverseString(lcs);
    printf("Longest Common Subsequence: %s\n", lcs);
    free(lcs);

    return 0;
}