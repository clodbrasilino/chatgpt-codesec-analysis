#include <stdio.h>
#include <string.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

int findShortestString(char* str1, char* str2) {
    int len1 = strlen(str1);
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
    char str1[100], str2[100];

    printf("Enter first string: ");
    gets(str1);
    printf("Enter second string: ");
    gets(str2);

    int result = findShortestString(str1, str2);
    printf("Length of shortest string: %d\n", result);

    return 0;
}