#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static size_t bounded_strlen(const char *s, size_t maxlen) {
    size_t len = 0;
    if (s) {
        while (len < maxlen && s[len] != '\0') {
            ++len;
        }
    }
    return len;
}

int shortest_common_supersequence_length(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    size_t max_str_len = (size_t)INT_MAX + 1;

    size_t len1 = bounded_strlen(str1, max_str_len);
    size_t len2 = bounded_strlen(str2, max_str_len);

    if (len1 > (size_t)INT_MAX || len2 > (size_t)INT_MAX || len1 == max_str_len || len2 == max_str_len) {
        return -1;
    }

    int m = (int)len1;
    int n = (int)len2;

    int *prev = calloc((size_t)n + 1, sizeof(*prev));
    int *curr = calloc((size_t)n + 1, sizeof(*curr));
    if (prev == NULL || curr == NULL) {
        free(prev);
        free(curr);
        return -1;
    }

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (str1[i - 1] == str2[j - 1]) {
                curr[j] = prev[j - 1] + 1;
            } else {
                curr[j] = prev[j] > curr[j - 1] ? prev[j] : curr[j - 1];
            }
        }

        int *tmp = prev;
        prev = curr;
        curr = tmp;
    }

    int lcs = prev[n];
    size_t scs_len = (size_t)m + (size_t)n - (size_t)lcs;

    free(prev);
    free(curr);

    if (scs_len > (size_t)INT_MAX) {
        return -1;
    }

    return (int)scs_len;
}

int main(void) {
    printf("%d\n", shortest_common_supersequence_length("AGGTAB", "GXTXAYB"));
    printf("%d\n", shortest_common_supersequence_length("abc", "abc"));
    printf("%d\n", shortest_common_supersequence_length("abc", ""));
    printf("%d\n", shortest_common_supersequence_length("", ""));
    printf("%d\n", shortest_common_supersequence_length(NULL, "abc"));
    return 0;
}