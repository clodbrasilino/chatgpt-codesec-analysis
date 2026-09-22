#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int max(int a, int b) {
    return (a > b) ? a : b;
}

int longest_repeating_subsequence(const char *str) {
    if (str == NULL) return 0;

    size_t len = strnlen(str, 4096);
    int n = (int)len;
    if (n == 0) return 0;

    int *dp = (int *)calloc((size_t)(n + 1) * (size_t)(n + 1), sizeof(int));
    if (!dp) return -1;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (str[i - 1] == str[j - 1] && i != j) {
                dp[i * (n + 1) + j] = dp[(i - 1) * (n + 1) + (j - 1)] + 1;
            } else {
                dp[i * (n + 1) + j] = max(dp[(i - 1) * (n + 1) + j], dp[i * (n + 1) + (j - 1)]);
            }
        }
    }

    int result = dp[n * (n + 1) + n];
    free(dp);
    return result;
}

int main(void) {
    const char *test1 = "ATACTCGGA";
    const char *test2 = "AABEBCDD";
    const char *test3 = "abcabc";
    const char *test4 = "";
    const char *test5 = "aaaa";

    printf("%d\n", longest_repeating_subsequence(test1));
    printf("%d\n", longest_repeating_subsequence(test2));
    printf("%d\n", longest_repeating_subsequence(test3));
    printf("%d\n", longest_repeating_subsequence(test4));
    printf("%d\n", longest_repeating_subsequence(test5));

    return 0;
}