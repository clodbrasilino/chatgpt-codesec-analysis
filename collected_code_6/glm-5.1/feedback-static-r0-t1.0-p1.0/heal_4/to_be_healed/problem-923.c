#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int shortest_supersequence(const char *str1, size_t m, const char *str2, size_t n) {
    size_t total_elements = (m + 1) * (n + 1);
    int *dp_block = (int *)malloc(total_elements * sizeof(int));
    if (dp_block == NULL) {
        return -1;
    }

    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    if (dp == NULL) {
        free(dp_block);
        return -1;
    }

    for (size_t i = 0; i <= m; i++) {
        dp[i] = dp_block + i * (n + 1);
    }

    for (size_t i = 0; i <= m; i++) {
        for (size_t j = 0; j <= n; j++) {
            if (i == 0) {
                dp[i][j] = j;
            } else if (j == 0) {
                dp[i][j] = i;
            } else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + (dp[i - 1][j] > dp[i][j - 1] ? dp[i][j - 1] : dp[i - 1][j]);
            }
        }
    }

    int result = dp[m][n];
    free(dp);
    free(dp_block);
    return result;
}

int main() {
    const char str1[] = "AGGTAB";
    const char str2[] = "GXTXAYB";
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str1_buf[256];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str2_buf[256];
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str1_buf, str1, sizeof(str1));
    str1_buf[sizeof(str1) - 1] = '\0';
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str2_buf, str2, sizeof(str2));
    str2_buf[sizeof(str2) - 1] = '\0';
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. Risk is low because the source is a constant character. (risk 1, buffer)
     */
    strncat(str1_buf, "", sizeof(str1_buf) - strlen(str1_buf) - 1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. Risk is low because the source is a constant character. (risk 1, buffer)
     */
    strncat(str2_buf, "", sizeof(str2_buf) - strlen(str2_buf) - 1);
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int result = shortest_supersequence(str1_buf, strlen(str1_buf), str2_buf, strlen(str2_buf));
    printf("%d\n", result);
    return 0;
}