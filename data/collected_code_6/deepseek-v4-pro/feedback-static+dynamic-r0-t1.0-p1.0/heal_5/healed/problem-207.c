#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int max_int(int a, int b) {
    return a > b ? a : b;
}

size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

int longest_repeating_subsequence(const char *str) {
    size_t n;
    int *dp;
    int *prev;
    size_t i;
    size_t j;
    int result;

    if (str == NULL) {
        return 0;
    }

    n = safe_strlen(str, 10000);
    if (n == 0) {
        return 0;
    }

    dp = (int *)calloc(n + 1, sizeof(int));
    if (dp == NULL) {
        return 0;
    }

    prev = (int *)calloc(n + 1, sizeof(int));
    if (prev == NULL) {
        free(dp);
        return 0;
    }

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (str[i - 1] == str[j - 1] && i != j) {
                dp[j] = prev[j - 1] + 1;
            } else {
                dp[j] = max_int(prev[j], dp[j - 1]);
            }
        }
        memcpy(prev, dp, (n + 1) * sizeof(int));
    }

    result = dp[n];

    free(dp);
    free(prev);

    return result;
}

int main(void) {
    const char *test1 = "aabebcdd";
    const char *test2 = "aabb";
    const char *test3 = "axxxy";
    const char *test4 = "";
    const char *test5 = NULL;

    printf("%d\n", longest_repeating_subsequence(test1));
    printf("%d\n", longest_repeating_subsequence(test2));
    printf("%d\n", longest_repeating_subsequence(test3));
    printf("%d\n", longest_repeating_subsequence(test4));
    printf("%d\n", longest_repeating_subsequence(test5));

    return 0;
}