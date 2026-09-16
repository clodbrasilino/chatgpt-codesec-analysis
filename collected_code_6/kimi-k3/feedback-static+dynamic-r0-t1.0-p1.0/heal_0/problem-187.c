#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *find_lcs(const char *s1, const char *s2)
{
    if (s1 == NULL || s2 == NULL) {
        return NULL;
    }

    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);

    if (len1 == 0 || len2 == 0) {
        char *empty = (char *)malloc(1);
        if (empty != NULL) {
            empty[0] = '\0';
        }
        return empty;
    }

    size_t rows = len1 + 1;
    size_t cols = len2 + 1;

    if (rows > SIZE_MAX / cols) {
        return NULL;
    }

    size_t *dp = (size_t *)calloc(rows * cols, sizeof(size_t));
    if (dp == NULL) {
        return NULL;
    }

    for (size_t i = 1; i <= len1; i++) {
        for (size_t j = 1; j <= len2; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i * cols + j] = dp[(i - 1) * cols + (j - 1)] + 1;
            } else {
                size_t up = dp[(i - 1) * cols + j];
                size_t left = dp[i * cols + (j - 1)];
                dp[i * cols + j] = (up > left) ? up : left;
            }
        }
    }

    size_t lcs_len = dp[len1 * cols + len2];

    if (lcs_len == SIZE_MAX) {
        free(dp);
        return NULL;
    }

    char *lcs = (char *)malloc(lcs_len + 1);
    if (lcs == NULL) {
        free(dp);
        return NULL;
    }

    size_t i = len1;
    size_t j = len2;
    size_t k = lcs_len;
    lcs[k] = '\0';

    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            lcs[--k] = s1[i - 1];
            i--;
            j--;
        } else if (dp[(i - 1) * cols + j] > dp[i * cols + (j - 1)]) {
            i--;
        } else {
            j--;
        }
    }

    free(dp);
    return lcs;
}

int main(void)
{
    const char *seq1 = "AGGTAB";
    const char *seq2 = "GXTXAYB";

    char *result = find_lcs(seq1, seq2);
    if (result == NULL) {
        fprintf(stderr, "Error: failed to compute LCS\n");
        return EXIT_FAILURE;
    }

    printf("Sequence 1: %s\n", seq1);
    printf("Sequence 2: %s\n", seq2);
    printf("LCS: %s\n", result);
    printf("Length: %zu\n", strlen(result));

    free(result);
    return EXIT_SUCCESS;
}