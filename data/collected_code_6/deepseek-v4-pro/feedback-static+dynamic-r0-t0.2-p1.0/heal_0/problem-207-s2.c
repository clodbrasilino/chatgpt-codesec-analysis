#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int longest_repeating_subsequence(const char *str) {
    int n = strlen(str);
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)calloc(n + 1, sizeof(int));
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (str[i - 1] == str[j - 1] && i != j) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }

    int result = dp[n][n];

    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main(void) {
    char input[256];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    input[strcspn(input, "\n")] = '\0';

    if (strlen(input) == 0) {
        return 1;
    }

    printf("%d\n", longest_repeating_subsequence(input));

    return 0;
}