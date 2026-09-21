#include <stdio.h>
#include <string.h>

int shortestCommonSupersequence(const char* str1, const char* str2, size_t len1, size_t len2) {
    int dp[len1 + 1][len2 + 1];
    
    for (size_t i = 0; i <= len1; i++) {
        for (size_t j = 0; j <= len2; j++) {
            if (i == 0) {
                dp[i][j] = j;
            } else if (j == 0) {
                dp[i][j] = i;
            } else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + (dp[i - 1][j] < dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1]);
            }
        }
    }
    return dp[len1][len2];
}

int main() {
    char str1[] = "AGGTAB\0";
    char str2[] = "GXTXAYB\0";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1 = strlen(str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = strlen(str2);
    printf("Length of the shortest common supersequence: %d\n", shortestCommonSupersequence(str1, str2, len1, len2));
    return 0;
}