#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *longest_palindromic_subsequence(const char *str) {
    if (str == NULL) {
        char *empty = (char *)malloc(1);
        if (!empty) return NULL;
        empty[0] = '\0';
        return empty;
    }

    size_t n = strlen(str);
    if (n == 0) {
        char *empty = (char *)malloc(1);
        if (!empty) return NULL;
        empty[0] = '\0';
        return empty;
    }

    int **dp = (int **)malloc(n * sizeof(int *));
    if (!dp) return NULL;
    for (size_t i = 0; i < n; i++) {
        dp[i] = (int *)calloc(n, sizeof(int));
        if (!dp[i]) {
            for (size_t k = 0; k < i; k++) free(dp[k]);
            free(dp);
            return NULL;
        }
        dp[i][i] = 1;
    }

    for (size_t len = 2; len <= n; len++) {
        for (size_t i = 0; i <= n - len; i++) {
            size_t j = i + len - 1;
            if (str[i] == str[j] && len == 2) {
                dp[i][j] = 2;
            } else if (str[i] == str[j]) {
                dp[i][j] = dp[i + 1][j - 1] + 2;
            } else {
                dp[i][j] = (dp[i + 1][j] > dp[i][j - 1]) ? dp[i + 1][j] : dp[i][j - 1];
            }
        }
    }

    int lps_length = dp[0][n - 1];
    char *result = (char *)malloc((size_t)(lps_length + 1) * sizeof(char));
    if (!result) {
        for (size_t i = 0; i < n; i++) free(dp[i]);
        free(dp);
        return NULL;
    }

    size_t i = 0, j = n - 1;
    size_t left = 0, right = (size_t)lps_length - 1;
    char *temp = (char *)malloc((size_t)(lps_length + 1) * sizeof(char));
    if (!temp) {
        free(result);
        for (size_t k = 0; k < n; k++) free(dp[k]);
        free(dp);
        return NULL;
    }

    while (i <= j) {
        if (str[i] == str[j]) {
            if (left <= right && left < (size_t)lps_length && right < (size_t)lps_length) {
                temp[left++] = str[i];
                temp[right--] = str[j];
            }
            i++;
            j--;
        } else if (i + 1 < n && dp[i + 1][j] > dp[i][j - 1]) {
            i++;
        } else {
            j--;
        }
    }

    temp[lps_length] = '\0';
    size_t result_size = (size_t)(lps_length + 1);
    size_t temp_len = strlen(temp);
    if (temp_len >= result_size) {
        temp[result_size - 1] = '\0';
    }
    memcpy(result, temp, result_size);
    free(temp);

    for (size_t k = 0; k < n; k++) free(dp[k]);
    free(dp);

    return result;
}

int main(void) {
    const char *test_strings[] = {
        "babad",
        "cbbd",
        "a",
        "",
        "character",
        "forgeeksskeegfor"
    };
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (size_t i = 0; i < num_tests; i++) {
        char *lps = longest_palindromic_subsequence(test_strings[i]);
        if (lps) {
            printf("Input: \"%s\"\nLongest Palindromic Subsequence: \"%s\"\n\n", test_strings[i], lps);
            free(lps);
        } else {
            printf("Input: \"%s\"\nMemory allocation failed\n\n", test_strings[i]);
        }
    }

    return 0;
}