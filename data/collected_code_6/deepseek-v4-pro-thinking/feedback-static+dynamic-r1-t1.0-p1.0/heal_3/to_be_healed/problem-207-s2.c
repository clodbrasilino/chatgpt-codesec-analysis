#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int longest_repeating_subsequence(const char *str, size_t n) {
    if (str == NULL || n == 0) return 0;
    size_t size = n + 1;
    if (size > SIZE_MAX / sizeof(int) / size) return -1;
    int *dp = calloc(size * size, sizeof(int));
    if (dp == NULL) return -1;
    for (size_t i = 1; i <= n; ++i) {
        for (size_t j = 1; j <= n; ++j) {
            size_t idx = i * size + j;
            if (str[i - 1] == str[j - 1] && i != j) {
                dp[idx] = dp[(i - 1) * size + (j - 1)] + 1;
            } else {
                int left = dp[(i - 1) * size + j];
                int up = dp[i * size + (j - 1)];
                dp[idx] = left > up ? left : up;
            }
        }
    }
    int result = dp[n * size + n];
    free(dp);
    return result;
}

int main(void) {
    const char *test_strings[] = {"AABEBCDD", "aaaa", "abcda", "", "axxxy"};
    /* Possible weaknesses found:
     *  Variable 'test_lengths' can be declared as const array [constVariable]
     */
    size_t test_lengths[] = {8, 4, 5, 0, 5};
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    for (size_t i = 0; i < num_tests; ++i) {
        printf("%s: %d\n", test_strings[i], longest_repeating_subsequence(test_strings[i], test_lengths[i]));
    }
    return 0;
}