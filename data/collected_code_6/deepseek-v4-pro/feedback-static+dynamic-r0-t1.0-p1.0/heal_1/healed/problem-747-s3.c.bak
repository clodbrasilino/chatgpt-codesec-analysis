#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* lcs_three(const char* s1, const char* s2, const char* s3) {
    int m = strlen(s1);
    int n = strlen(s2);
    int p = strlen(s3);
    
    int*** dp = (int***)malloc((m + 1) * sizeof(int**));
    if (!dp) return NULL;
    
    for (int i = 0; i <= m; i++) {
        dp[i] = (int**)malloc((n + 1) * sizeof(int*));
        if (!dp[i]) {
            for (int j = 0; j < i; j++) {
                for (int k = 0; k <= n; k++) free(dp[j][k]);
                free(dp[j]);
            }
            free(dp);
            return NULL;
        }
        for (int j = 0; j <= n; j++) {
            dp[i][j] = (int*)malloc((p + 1) * sizeof(int));
            if (!dp[i][j]) {
                for (int k = 0; k < j; k++) free(dp[i][k]);
                free(dp[i]);
                for (int l = 0; l < i; l++) {
                    for (int k = 0; k <= n; k++) free(dp[l][k]);
                    free(dp[l]);
                }
                free(dp);
                return NULL;
            }
        }
    }
    
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= p; k++) {
                if (i == 0 || j == 0 || k == 0) {
                    dp[i][j][k] = 0;
                } else if (s1[i-1] == s2[j-1] && s1[i-1] == s3[k-1]) {
                    dp[i][j][k] = dp[i-1][j-1][k-1] + 1;
                } else {
                    int max = dp[i-1][j][k];
                    if (dp[i][j-1][k] > max) max = dp[i][j-1][k];
                    if (dp[i][j][k-1] > max) max = dp[i][j][k-1];
                    if (dp[i-1][j-1][k] > max) max = dp[i-1][j-1][k];
                    if (dp[i-1][j][k-1] > max) max = dp[i-1][j][k-1];
                    if (dp[i][j-1][k-1] > max) max = dp[i][j-1][k-1];
                    dp[i][j][k] = max;
                }
            }
        }
    }
    
    int len = dp[m][n][p];
    char* result = (char*)malloc((len + 1) * sizeof(char));
    if (!result) {
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) free(dp[i][j]);
            free(dp[i]);
        }
        free(dp);
        return NULL;
    }
    
    result[len] = '\0';
    int x = m, y = n, z = p;
    int index = len - 1;
    
    while (x > 0 && y > 0 && z > 0) {
        if (s1[x-1] == s2[y-1] && s1[x-1] == s3[z-1]) {
            result[index] = s1[x-1];
            x--; y--; z--; index--;
        } else if (dp[x-1][y][z] >= dp[x][y-1][z] && dp[x-1][y][z] >= dp[x][y][z-1]) {
            x--;
        } else if (dp[x][y-1][z] >= dp[x-1][y][z] && dp[x][y-1][z] >= dp[x][y][z-1]) {
            y--;
        } else {
            z--;
        }
    }
    
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) free(dp[i][j]);
        free(dp[i]);
    }
    free(dp);
    
    return result;
}

int main(void) {
    const char* str1 = "ABCDGH";
    const char* str2 = "AEDFHR";
    const char* str3 = "ADH";
    
    char* result = lcs_three(str1, str2, str3);
    
    if (result) {
        printf("LCS of three strings: %s\n", result);
        printf("Length: %zu\n", strlen(result));
        free(result);
    } else {
        printf("Error computing LCS\n");
    }
    
    const char* test1_a = "AGGT12";
    const char* test1_b = "12TXAYB";
    const char* test1_c = "12XBA";
    result = lcs_three(test1_a, test1_b, test1_c);
    if (result) {
        printf("LCS: %s\n", result);
        free(result);
    }
    
    const char* test2_a = "";
    const char* test2_b = "ABC";
    const char* test2_c = "DEF";
    result = lcs_three(test2_a, test2_b, test2_c);
    if (result) {
        printf("LCS with empty string: '%s'\n", result);
        free(result);
    }
    
    return 0;
}