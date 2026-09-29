#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longest_repeating_subsequence(const char *str, size_t len) {
    if (str == NULL) return -1;
    if (len == 0) return 0;
    if (len == (size_t)-1) return -1;
    size_t n = len;
    size_t row_len = n + 1;
    if (row_len > (size_t)-1 / row_len) return -1;
    size_t elems = row_len * row_len;
    if (elems > (size_t)-1 / sizeof(int)) return -1;
    int *dp = (int *)malloc(elems * sizeof(int));
    if (dp == NULL) return -1;
    for (size_t i = 0; i <= n; ++i) dp[i * row_len] = 0;
    for (size_t j = 0; j <= n; ++j) dp[j] = 0;
    for (size_t i = 1; i <= n; ++i) {
        for (size_t j = 1; j <= n; ++j) {
            if (str[i - 1] == str[j - 1] && i != j) {
                dp[i * row_len + j] = dp[(i - 1) * row_len + (j - 1)] + 1;
            } else {
                int left = dp[(i - 1) * row_len + j];
                int up = dp[i * row_len + (j - 1)];
                dp[i * row_len + j] = left > up ? left : up;
            }
        }
    }
    int result = dp[n * row_len + n];
    free(dp);
    return result;
}

int main(void) {
    const char *s = "aabebcdd";
    int length = longest_repeating_subsequence(s, strlen(s));
    if (length < 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    printf("%d\n", length);
    return 0;
}