#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int longestRepeatingSubseq(const char *str, size_t buffer_size) {
    size_t n = strnlen(str, buffer_size);
    if (n == 0) {
        return 0;
    }
    int **dp = malloc((n + 1) * sizeof(int *));
    if (dp == NULL) {
        return -1;
    }
    for (size_t i = 0; i <= n; i++) {
        dp[i] = malloc((n + 1) * sizeof(int));
        if (dp[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return -1;
        }
    }
    for (size_t i = 0; i <= n; i++) {
        for (size_t j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (str[i - 1] == str[j - 1] && i != j) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    int result = dp[n][n];
    for (size_t i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);
    return result;
}

int main(void) {
    char str[1024];
    if (fgets(str, sizeof(str), stdin) != NULL) {
        size_t len = strlen(str);
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
        }
        int result = longestRepeatingSubseq(str, sizeof(str));
        if (result >= 0) {
            printf("%d\n", result);
        } else {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
    } else {
        fprintf(stderr, "Input reading failed\n");
        return 1;
    }
    return 0;
}