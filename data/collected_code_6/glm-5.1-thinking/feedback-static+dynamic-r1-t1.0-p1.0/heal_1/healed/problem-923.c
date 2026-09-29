#include <stdio.h>
#include <stdlib.h>

int shortestSupersequenceLength(const char *str1, size_t len1, const char *str2, size_t len2) {
    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    size_t m = len1;
    size_t n = len2;
    size_t cols = n + 1;

    int *dp = malloc((m + 1) * cols * sizeof(int));
    if (dp == NULL) {
        return -1;
    }

    for (size_t i = 0; i <= m; i++) {
        for (size_t j = 0; j <= n; j++) {
            if (i == 0) {
                dp[i * cols + j] = j;
            } else if (j == 0) {
                dp[i * cols + j] = i;
            } else if (str1[i - 1] == str2[j - 1]) {
                dp[i * cols + j] = 1 + dp[(i - 1) * cols + (j - 1)];
            } else {
                int val1 = dp[(i - 1) * cols + j];
                int val2 = dp[i * cols + (j - 1)];
                dp[i * cols + j] = 1 + (val1 < val2 ? val1 : val2);
            }
        }
    }

    int result = dp[m * cols + n];
    free(dp);

    return result;
}

int main(void) {
    const char *str1 = "abac";
    const char *str2 = "cab";
    int result = shortestSupersequenceLength(str1, sizeof("abac") - 1, str2, sizeof("cab") - 1);
    printf("%d\n", result);
    return 0;
}