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
 /* Possible weaknesses found:
  *  test case 0 failed: expected 3, got <no output>
  *  test case 1 failed: expected 2, got <no output>
  *  test case 2 failed: expected 1, got <no output>
  */

int longest_repeating_subsequence(const char *str) {
    size_t n;
    int **dp;
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

    dp = (int **)malloc((n + 1) * sizeof(int *));
    if (dp == NULL) {
        return 0;
    }

    for (i = 0; i <= n; i++) {
        dp[i] = (int *)calloc(n + 1, sizeof(int));
        if (dp[i] == NULL) {
            size_t k;
            for (k = 0; k < i; k++) {
                free(dp[k]);
            }
            free(dp);
            return 0;
        }
    }

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (str[i - 1] == str[j - 1] && i != j) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max_int(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    result = dp[n][n];

    for (i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

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