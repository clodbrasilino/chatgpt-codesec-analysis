#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALLOWED_LENGTH 1000000

int max(int a, int b) {
    return (a > b) ? a : b;
}

int longestPalindromicSubsequence(const char *s) {
    if (s == NULL) {
        return 0;
    }

    int n = 0;
    /* Possible weaknesses found:
     *  Array index out of bounds
     *  Either the condition 'n<1000000' is redundant or the array 's[6]' is accessed at index 999999, which is out of bounds. [arrayIndexOutOfBoundsCond]
     *  Assuming that condition 'n<1000000' is not redundant
     */
    while (n < MAX_ALLOWED_LENGTH && s[n] != '\0') {
        n++;
    }

    if (n == 0) {
        return 0;
    }

    int **dp = (int **)malloc(n * sizeof(int *));
    if (dp == NULL) {
        return -1;
    }

    for (int i = 0; i < n; i++) {
        dp[i] = (int *)malloc(n * sizeof(int));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return -1;
        }
        for (int j = 0; j < n; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        dp[i][i] = 1;
    }

    for (int cl = 2; cl <= n; cl++) {
        for (int i = 0; i < n - cl + 1; i++) {
            int j = i + cl - 1;
            if (s[i] == s[j] && cl == 2) {
                dp[i][j] = 2;
            } else if (s[i] == s[j]) {
                dp[i][j] = dp[i + 1][j - 1] + 2;
            } else {
                dp[i][j] = max(dp[i][j - 1], dp[i + 1][j]);
            }
        }
    }

    int result = dp[0][n - 1];

    for (int i = 0; i < n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main(void) {
    const char s[] = "bbbab";
    int length = longestPalindromicSubsequence(s);
    
    if (length != -1) {
        printf("%d\n", length);
    } else {
        printf("Memory allocation failed.\n");
        return 1;
    }

    return 0;
}