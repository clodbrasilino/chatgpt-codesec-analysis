#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int longest_repeating_subsequence(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t len = strnlen(str, 200);
    if (len == 0) {
        return 0;
    }

    int n = (int)len;
    if (n > 199) {
        n = 199;
    }

    int *dp = calloc(200 * 200, sizeof(int));
    if (dp == NULL) {
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (str[i - 1] == str[j - 1] && i != j) {
                dp[i * 200 + j] = dp[(i - 1) * 200 + (j - 1)] + 1;
            } else {
                int left = dp[(i - 1) * 200 + j];
                int up = dp[i * 200 + (j - 1)];
                dp[i * 200 + j] = (left > up) ? left : up;
            }
        }
    }

    int result = dp[n * 200 + n];
    free(dp);
    return result;
}

int main(void) {
    const char *test1 = "AABEBCDD";
    const char *test2 = "axxxy";
    const char *test3 = "aab";
    const char *test4 = "abc";
    const char *test5 = "";
    const char *test6 = NULL;

    printf("Longest repeating subsequence of %s: %d\n", test1, longest_repeating_subsequence(test1));
    printf("Longest repeating subsequence of %s: %d\n", test2, longest_repeating_subsequence(test2));
    printf("Longest repeating subsequence of %s: %d\n", test3, longest_repeating_subsequence(test3));
    printf("Longest repeating subsequence of %s: %d\n", test4, longest_repeating_subsequence(test4));
    printf("Longest repeating subsequence of %s: %d\n", test5, longest_repeating_subsequence(test5));
    printf("Longest repeating subsequence of NULL: %d\n", longest_repeating_subsequence(test6));

    return 0;
}