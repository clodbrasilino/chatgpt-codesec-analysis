#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longest_repeating_subsequence(const char *str) {
    size_t n, i, j, elems;
    int *dp;
    int result;

    if (str == NULL) return -1;
    n = strlen(str);
    if (n + 1 > (size_t)-1 / (n + 1)) return -1;
    elems = (n + 1) * (n + 1);
    if (elems > (size_t)-1 / sizeof(int)) return -1;

    dp = (int *)malloc(elems * sizeof(int));
    if (dp == NULL) return -1;

    for (i = 0; i <= n; ++i) dp[i * (n + 1)] = 0;
    for (j = 0; j <= n; ++j) dp[j] = 0;

    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= n; ++j) {
            if (str[i - 1] == str[j - 1] && i != j) {
                dp[i * (n + 1) + j] = dp[(i - 1) * (n + 1) + (j - 1)] + 1;
            } else {
                int left = dp[(i - 1) * (n + 1) + j];
                int up = dp[i * (n + 1) + (j - 1)];
                dp[i * (n + 1) + j] = left > up ? left : up;
            }
        }
    }

    result = dp[n * (n + 1) + n];
    free(dp);
    return result;
}

int main(void) {
    const char *s = "aabebcdd";
    int length = longest_repeating_subsequence(s);

    if (length < 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("%d\n", length);
    return 0;
}