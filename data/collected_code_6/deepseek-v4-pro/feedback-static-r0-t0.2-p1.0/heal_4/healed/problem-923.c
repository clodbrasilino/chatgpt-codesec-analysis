#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    if (len == max_len) {
        return -1;
    }
    return (int)len;
}

int shortest_common_supersequence_length(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    int len1_int = safe_strlen(str1, (size_t)-1);
    int len2_int = safe_strlen(str2, (size_t)-1);

    if (len1_int < 0 || len2_int < 0) {
        return -1;
    }

    size_t len1 = (size_t)len1_int;
    size_t len2 = (size_t)len2_int;

    size_t max_size = (size_t)-1;

    if (len1 > max_size / sizeof(int *) - 1 ||
        len2 > max_size / sizeof(int) - 1) {
        return -1;
    }

    size_t rows = len1 + 1;
    size_t cols = len2 + 1;

    int **dp = (int **)malloc(rows * sizeof(int *));
    if (dp == NULL) {
        return -1;
    }

    size_t i;
    int allocation_failed = 0;

    for (i = 0; i < rows; i++) {
        dp[i] = (int *)malloc(cols * sizeof(int));
        if (dp[i] == NULL) {
            allocation_failed = 1;
            break;
        }
    }

    if (allocation_failed) {
        for (size_t j = 0; j < i; j++) {
            free(dp[j]);
        }
        free(dp);
        return -1;
    }

    for (i = 0; i < rows; i++) {
        size_t j;
        for (j = 0; j < cols; j++) {
            if (i == 0) {
                dp[i][j] = (int)j;
            } else if (j == 0) {
                dp[i][j] = (int)i;
            } else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                int left = dp[i][j - 1];
                int up = dp[i - 1][j];
                dp[i][j] = (left < up ? left : up) + 1;
            }
        }
    }

    int result = dp[len1][len2];

    for (i = 0; i < rows; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main(void) {
    const char str1[] = "AGGTAB";
    const char str2[] = "GXTXAYB";
    int result = shortest_common_supersequence_length(str1, str2);
    if (result != -1) {
        printf("%d\n", result);
    } else {
        printf("Memory allocation failed\n");
    }
    return 0;
}