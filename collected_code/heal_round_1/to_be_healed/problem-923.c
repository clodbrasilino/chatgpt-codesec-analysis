#include <stdio.h>
#include <string.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

int findShortestString(char* str1, char* str2) {
    /* Possible weaknesses found:
     *  Cannot determine that 'str1[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int len1 = strlen(str1);
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 'str2[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
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
                /* Possible weaknesses found:
                 *  implicit declaration of function 'max' [-Wimplicit-function-declaration]
                 */
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
    char str1[100], str2[100];

    printf("Enter first string: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'str1[0]' is initialized [premium-bughuntingUninit]
     *   Does not check for buffer overflows (CWE-120, CWE-20). Use fgets() instead.
     */
    gets(str1);
    printf("Enter second string: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'str2[0]' is initialized [premium-bughuntingUninit]
     *   Does not check for buffer overflows (CWE-120, CWE-20). Use fgets() instead.
     */
    gets(str2);

    int result = findShortestString(str1, str2);
    printf("Length of shortest string: %d\n", result);

    return 0;
}