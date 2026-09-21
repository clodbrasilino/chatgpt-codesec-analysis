#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 4096
#define IDX(i, j, k) ((i) * (len2 + 1) * (len3 + 1) + (j) * (len3 + 1) + (k))

int max(int a, int b) {
    return (a > b) ? a : b;
}

size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

int lcsOfThree(const char* s1, const char* s2, const char* s3) {
    if (!s1 || !s2 || !s3) return 0;

    size_t len1 = safe_strlen(s1, MAX_LEN);
    size_t len2 = safe_strlen(s2, MAX_LEN);
    size_t len3 = safe_strlen(s3, MAX_LEN);

    int* dp = (int*)calloc((len1 + 1) * (len2 + 1) * (len3 + 1), sizeof(int));
    if (!dp) return -1;

    for (size_t i = 1; i <= len1; i++) {
        for (size_t j = 1; j <= len2; j++) {
            for (size_t k = 1; k <= len3; k++) {
                if (s1[i - 1] == s2[j - 1] && s1[i - 1] == s3[k - 1]) {
                    dp[IDX(i, j, k)] = dp[IDX(i - 1, j - 1, k - 1)] + 1;
                } else {
                    dp[IDX(i, j, k)] = max(max(dp[IDX(i - 1, j, k)], dp[IDX(i, j - 1, k)]), dp[IDX(i, j, k - 1)]);
                }
            }
        }
    }

    int result = dp[IDX(len1, len2, len3)];

    free(dp);

    return result;
}

int main(void) {
    const char* s1 = "geeks";
    const char* s2 = "geeksfor";
    const char* s3 = "geeksforgeeks";

    int result = lcsOfThree(s1, s2, s3);
    
    if (result == -1) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Length of LCS is %d\n", result);

    return 0;
}