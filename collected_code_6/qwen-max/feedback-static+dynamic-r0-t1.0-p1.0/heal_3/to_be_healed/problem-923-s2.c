#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int shortestCommonSupersequenceLength(const char *str1, const char *str2, size_t len1, size_t len2) {
    int dp[len1 + 1][len2 + 1];

    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = i + j;
            } else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = 1 + (dp[i - 1][j] < dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1]);
            }
        }
    }
    return dp[len1][len2];
}

int main() {
    /* Possible weaknesses found:
     *  Assignment 'str1="ABCD"', assigned value is "ABCD"
     */
    const char* str1 = "ABCD";
    /* Possible weaknesses found:
     *  Assignment 'str2="ACDF"', assigned value is "ACDF"
     */
    const char* str2 = "ACDF";
    /* Possible weaknesses found:
     *  Condition 'str1!=NULL' is always true [knownConditionTrueFalse]
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  Condition 'str1!=NULL' is always true
     */
    size_t len1 = (str1 != NULL) ? strlen(str1) : 0;
    /* Possible weaknesses found:
     *  Condition 'str2!=NULL' is always true [knownConditionTrueFalse]
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  Condition 'str2!=NULL' is always true
     */
    size_t len2 = (str2 != NULL) ? strlen(str2) : 0;
    int result = shortestCommonSupersequenceLength(str1, str2, len1, len2);
    printf("Length of the shortest common supersequence: %d\n", result);
    return 0;
}