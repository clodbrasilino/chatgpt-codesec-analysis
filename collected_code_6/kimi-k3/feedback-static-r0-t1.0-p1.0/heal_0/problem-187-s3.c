#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *lcs(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) {
        return NULL;
    }

    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);

    if (len1 == 0 || len2 == 0) {
        char *empty = malloc(1);
        if (empty != NULL) {
            empty[0] = '\0';
        }
        return empty;
    }

    if (len1 > SIZE_MAX / (len2 + 1) - 1) {
        return NULL;
    }

    size_t rows = len1 + 1;
    size_t cols = len2 + 1;
    size_t *dp = calloc(rows * cols, sizeof(size_t));
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
    char *result = malloc(lcs_len + 1);
    if (result == NULL) {
        free(dp);
        return NULL;
    }

    size_t i = len1;
    size_t j = len2;
    size_t pos = lcs_len;
    result[pos] = '\0';

    while (i > 0 && j > 0 && pos > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            result[--pos] = s1[i - 1];
            i--;
            j--;
        } else if (dp[(i - 1) * cols + j] > dp[i * cols + (j - 1)]) {
            i--;
        } else {
            j--;
        }
    }

    free(dp);
    return result;
}

int main(void) {
    const char *seq1 = "ABCBDAB";
    const char *seq2 = "BDCABA";

    char *result = lcs(seq1, seq2);
    if (result == NULL) {
        fprintf(stderr, "Error: failed to compute LCS\n");
        return EXIT_FAILURE;
    }

    printf("Sequence 1: %s\n", seq1);
    printf("Sequence 2: %s\n", seq2);
    printf("LCS: %s\n", result);
    printf("LCS Length: %zu\n", strlen(result));

    free(result);
    return EXIT_SUCCESS;
}