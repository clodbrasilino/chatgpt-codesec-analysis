#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longest_repeating_subsequence(const char *str) {
    if (str == NULL) return -1;
    size_t n = strlen(str);
    if (n == 0) return 0;
    if (n > (size_t)-1 / sizeof(int) - 1) return -1;

    int *prev = (int *)calloc(n + 1, sizeof(int));
    int *curr = (int *)calloc(n + 1, sizeof(int));
    if (prev == NULL || curr == NULL) {
        free(prev);
        free(curr);
        return -1;
    }

    for (size_t i = 1; i <= n; ++i) {
        for (size_t j = 1; j <= n; ++j) {
            if (str[i - 1] == str[j - 1] && i != j) {
                curr[j] = prev[j - 1] + 1;
            } else {
                int left = prev[j];
                int up = curr[j - 1];
                curr[j] = left > up ? left : up;
            }
        }
        int *tmp = prev;
        prev = curr;
        curr = tmp;
    }

    int result = prev[n];
    free(prev);
    free(curr);
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