#include <stdio.h>
#include <string.h>

#define MAX_STR_LEN 100

int min(int a, int b) {
    return (a < b) ? a : b;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int findShortestString(const char* str1, const char* str2) {
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int len1 = strlen(str1);
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int len2 = strlen(str2);
    int dp[len1+1][len2+1];

    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (str1[i-1] == str2[j-1])
                dp[i][j] = dp[i-1][j-1] + 1;
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }

    int lcsLength = dp[len1][len2];
    int shortestLength = len1 + len2 - lcsLength;
    return shortestLength;
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str1[MAX_STR_LEN], str2[MAX_STR_LEN];

    printf("Enter first string: ");
    fgets(str1, MAX_STR_LEN, stdin);

    printf("Enter second string: ");
    fgets(str2, MAX_STR_LEN, stdin);

    str1[strcspn(str1, "\n")] = 0;
    str2[strcspn(str2, "\n")] = 0;

    int result = findShortestString(str1, str2);
    printf("Length of shortest string: %d\n", result);

    return 0;
}