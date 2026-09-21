#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t get_longest_repeating_subsequence_length(const char *str, size_t max_len);

size_t get_longest_repeating_subsequence_length(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }

    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }

    if (len == 0 || len >= ((size_t)-1) / 2) {
        return 0;
    }

    size_t dim = len + 1;
    if (dim > ((size_t)-1) / dim) {
        return 0;
    }

    size_t *dp = (size_t *)calloc(dim * dim, sizeof(size_t));
    if (dp == NULL) {
        return 0;
    }

    for (size_t i = 1; i <= len; i++) {
        for (size_t j = 1; j <= len; j++) {
            if (str[i - 1] == str[j - 1] && i != j) {
                dp[i * dim + j] = 1 + dp[(i - 1) * dim + (j - 1)];
            } else {
                size_t val1 = dp[i * dim + (j - 1)];
                size_t val2 = dp[(i - 1) * dim + j];
                dp[i * dim + j] = (val1 > val2) ? val1 : val2;
            }
        }
    }

    size_t result = dp[len * dim + len];
    free(dp);

    return result;
}

int main(void) {
    const char test_str[] = "aabebcdd";
    
    size_t length = get_longest_repeating_subsequence_length(test_str, sizeof(test_str));
    
    printf("%zu\n", length);
    
    return 0;
}