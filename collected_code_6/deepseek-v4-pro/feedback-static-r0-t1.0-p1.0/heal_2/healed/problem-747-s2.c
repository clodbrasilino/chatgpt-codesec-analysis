#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* lcs_three(const char *s1, const char *s2, const char *s3) {
    if (s1 == NULL || s2 == NULL || s3 == NULL) {
        return NULL;
    }

    int len1 = 0;
    while (s1[len1] != '\0') len1++;
    int len2 = 0;
    while (s2[len2] != '\0') len2++;
    int len3 = 0;
    while (s3[len3] != '\0') len3++;
    
    int ***dp = (int***)malloc((len1 + 1) * sizeof(int**));
    if (dp == NULL) {
        return NULL;
    }

    for (int i = 0; i <= len1; i++) {
        dp[i] = (int**)malloc((len2 + 1) * sizeof(int*));
        if (dp[i] == NULL) {
            for (int x = 0; x < i; x++) {
                for (int y = 0; y <= len2; y++) {
                    free(dp[x][y]);
                }
                free(dp[x]);
            }
            free(dp);
            return NULL;
        }
        for (int j = 0; j <= len2; j++) {
            dp[i][j] = (int*)calloc(len3 + 1, sizeof(int));
            if (dp[i][j] == NULL) {
                for (int y = 0; y < j; y++) {
                    free(dp[i][y]);
                }
                free(dp[i]);
                for (int x = 0; x < i; x++) {
                    for (int y = 0; y <= len2; y++) {
                        free(dp[x][y]);
                    }
                    free(dp[x]);
                }
                free(dp);
                return NULL;
            }
        }
    }
    
    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            for (int k = 1; k <= len3; k++) {
                if (s1[i-1] == s2[j-1] && s2[j-1] == s3[k-1]) {
                    dp[i][j][k] = dp[i-1][j-1][k-1] + 1;
                } else {
                    int max = dp[i-1][j][k];
                    if (dp[i][j-1][k] > max) max = dp[i][j-1][k];
                    if (dp[i][j][k-1] > max) max = dp[i][j][k-1];
                    dp[i][j][k] = max;
                }
            }
        }
    }
    
    int index = dp[len1][len2][len3];
    char *result = (char*)malloc((index + 1) * sizeof(char));
    if (result == NULL) {
        for (int i = 0; i <= len1; i++) {
            for (int j = 0; j <= len2; j++) {
                free(dp[i][j]);
            }
            free(dp[i]);
        }
        free(dp);
        return NULL;
    }
    result[index] = '\0';
    
    int i = len1, j = len2, k = len3;
    while (i > 0 && j > 0 && k > 0) {
        if (s1[i-1] == s2[j-1] && s2[j-1] == s3[k-1]) {
            result[index-1] = s1[i-1];
            index--;
            i--; j--; k--;
        } else if (dp[i-1][j][k] >= dp[i][j-1][k] && dp[i-1][j][k] >= dp[i][j][k-1]) {
            i--;
        } else if (dp[i][j-1][k] >= dp[i-1][j][k] && dp[i][j-1][k] >= dp[i][j][k-1]) {
            j--;
        } else {
            k--;
        }
    }
    
    for (int x = 0; x <= len1; x++) {
        for (int y = 0; y <= len2; y++) {
            free(dp[x][y]);
        }
        free(dp[x]);
    }
    free(dp);
    
    return result;
}

int main(void) {
    const char str1[] = "ABCBDAB";
    const char str2[] = "BDCABA";
    const char str3[] = "BADBCA";
    
    char *lcs = lcs_three(str1, str2, str3);
    if (lcs != NULL) {
        printf("Longest Common Subsequence: %s\n", lcs);
        size_t length = 0;
        while (lcs[length] != '\0') length++;
        printf("Length: %zu\n", length);
        free(lcs);
    } else {
        printf("Error computing LCS.\n");
    }
    
    return 0;
}