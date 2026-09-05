#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_lcs_length(const char *s1, const char *s2, const char *s3) {
    if (s1 == NULL || s2 == NULL || s3 == NULL) {
        return -1;
    }

    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    size_t len3 = strlen(s3);

    if (len1 == 0 || len2 == 0 || len3 == 0) {
        return 0;
    }

    const size_t dims[3] = {len1 + 1, len2 + 1, len3 + 1};
    size_t total_size = dims[0] * dims[1] * dims[2];

    if (total_size / dims[0] != dims[1] * dims[2]) {
        return -1;
    }

    int *dp = (int *)calloc(total_size, sizeof(int));
    if (dp == NULL) {
        return -1;
    }

    size_t stride2 = dims[2];
    size_t stride1 = dims[1] * dims[2];

    for (size_t i = 1; i <= len1; i++) {
        for (size_t j = 1; j <= len2; j++) {
            for (size_t k = 1; k <= len3; k++) {
                size_t curr = i * stride1 + j * stride2 + k;
                if (s1[i - 1] == s2[j - 1] && s2[j - 1] == s3[k - 1]) {
                    dp[curr] = dp[(i - 1) * stride1 + (j - 1) * stride2 + (k - 1)] + 1;
                } else {
                    int a = dp[(i - 1) * stride1 + j * stride2 + k];
                    int b = dp[i * stride1 + (j - 1) * stride2 + k];
                    int c = dp[i * stride1 + j * stride2 + (k - 1)];
                    int max = (a > b) ? a : b;
                    dp[curr] = (max > c) ? max : c;
                }
            }
        }
    }

    int result = dp[len1 * stride1 + len2 * stride2 + len3];
    free(dp);
    return result;
}

int main(void) {
    const char *str1 = "AGGT12";
    const char *str2 = "12TXAYB";
    const char *str3 = "12XBA";

    int length = find_lcs_length(str1, str2, str3);

    if (length >= 0) {
        printf("Length of Longest Common Subsequence is %d\n", length);
    } else {
        fprintf(stderr, "Error occurred during computation\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}