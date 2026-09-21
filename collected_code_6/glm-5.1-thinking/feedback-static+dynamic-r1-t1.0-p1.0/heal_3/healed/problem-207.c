#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int longestRepeatingSubseq(const char *str, int n) {
    if (n <= 0) {
        return 0;
    }
    size_t num_ptrs = (size_t)n + 1;
    size_t num_ints = (size_t)n + 1;
    if (num_ptrs > SIZE_MAX / sizeof(int *) || num_ints > SIZE_MAX / sizeof(int)) {
        return -1;
    }
    int **dp = (int **)malloc(num_ptrs * sizeof(int *));
    if (dp == NULL) {
        return -1;
    }
    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)malloc(num_ints * sizeof(int));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return -1;
        }
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
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
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);
    return result;
}

int main(void) {
    size_t capacity = 128;
    char *str = malloc(capacity);
    if (str == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    size_t len = 0;
    int c;
    while ((c = getchar()) != EOF && c != '\n') {
        if (len + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(str);
                fprintf(stderr, "Memory allocation failed\n");
                return 1;
            }
            capacity *= 2;
            char *temp = realloc(str, capacity);
            if (temp == NULL) {
                free(str);
                fprintf(stderr, "Memory allocation failed\n");
                return 1;
            }
            str = temp;
        }
        str[len++] = c;
    }
    str[len] = '\0';
    
    if (len >= INT_MAX) {
        fprintf(stderr, "Input too long\n");
        free(str);
        return 1;
    }
    int n = (int)len;
    int result = longestRepeatingSubseq(str, n);
    if (result >= 0) {
        printf("%d\n", result);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        free(str);
        return 1;
    }
    free(str);
    return 0;
}