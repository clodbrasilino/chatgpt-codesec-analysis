#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 2048

int max(int a, int b) {
    return (a > b) ? a : b;
}

char* longestCommonSubsequence(const char* s1, const char* s2) {
    if (!s1 || !s2) return NULL;

    size_t sz1 = strnlen(s1, MAX_STR_LEN);
    size_t sz2 = strnlen(s2, MAX_STR_LEN);
    
    if (sz1 == MAX_STR_LEN || sz2 == MAX_STR_LEN) return NULL;

    int len1 = (int)sz1;
    int len2 = (int)sz2;

    int** dp = (int**)malloc((len1 + 1) * sizeof(int*));
    if (!dp) return NULL;
    for (int i = 0; i <= len1; i++) {
        dp[i] = (int*)calloc(len2 + 1, sizeof(int));
        if (!dp[i]) {
            for (int j = 0; j < i; j++) free(dp[j]);
            free(dp);
            return NULL;
        }
    }

    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    int index = dp[len1][len2];
    char* lcs = (char*)malloc((index + 1) * sizeof(char));
    if (!lcs) {
        for (int i = 0; i <= len1; i++) free(dp[i]);
        free(dp);
        return NULL;
    }
    lcs[index] = '\0';

    int i = len1, j = len2;
    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            lcs[index - 1] = s1[i - 1];
            i--;
            j--;
            index--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    for (int k = 0; k <= len1; k++) {
        free(dp[k]);
    }
    free(dp);

    return lcs;
}

int main(void) {
    const char* s1 = "AGGTAB";
    const char* s2 = "GXTXAYB";
    
    char* lcs = longestCommonSubsequence(s1, s2);
    
    if (lcs) {
        printf("%s\n", lcs);
        free(lcs);
    }
    
    return 0;
}