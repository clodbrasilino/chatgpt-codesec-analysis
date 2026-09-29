#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int shortest_supersequence_length(const char *str1, const char *str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int **dp = (int **)malloc((len1 + 1) * sizeof(int *));
    for (int i = 0; i <= len1; i++) {
        dp[i] = (int *)malloc((len2 + 1) * sizeof(int));
    }

    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            if (i == 0) {
                dp[i][j] = j;
            } else if (j == 0) {
                dp[i][j] = i;
            } else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = (dp[i - 1][j] < dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1]) + 1;
            }
        }
    }

    int result = dp[len1][len2];

    for (int i = 0; i <= len1; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main(void) {
    char str1[100];
    char str2[100];

    printf("Enter first string: ");
    if (scanf("%99s", str1) != 1) {
        return 1;
    }

    printf("Enter second string: ");
    if (scanf("%99s", str2) != 1) {
        return 1;
    }

    int length = shortest_supersequence_length(str1, str2);
    printf("Length of shortest common supersequence: %d\n", length);

    return 0;
}