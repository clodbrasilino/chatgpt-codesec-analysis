#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *find_lcs(const char *seq1, const char *seq2) {
    if (seq1 == NULL || seq2 == NULL) {
        return NULL;
    }

    size_t len1 = strlen(seq1);
    size_t len2 = strlen(seq2);

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

    size_t table_size = (len1 + 1) * (len2 + 1);
    int *dp = calloc(table_size, sizeof(int));
    if (dp == NULL) {
        return NULL;
    }

    for (size_t i = 1; i <= len1; i++) {
        for (size_t j = 1; j <= len2; j++) {
            size_t idx = i * (len2 + 1) + j;
            size_t idx_diag = (i - 1) * (len2 + 1) + (j - 1);
            size_t idx_up = (i - 1) * (len2 + 1) + j;
            size_t idx_left = i * (len2 + 1) + (j - 1);

            if (seq1[i - 1] == seq2[j - 1]) {
                dp[idx] = dp[idx_diag] + 1;
            } else {
                dp[idx] = (dp[idx_up] > dp[idx_left]) ? dp[idx_up] : dp[idx_left];
            }
        }
    }

    size_t lcs_len = (size_t)dp[len1 * (len2 + 1) + len2];
    char *lcs = malloc(lcs_len + 1);
    if (lcs == NULL) {
        free(dp);
        return NULL;
    }

    size_t i = len1;
    size_t j = len2;
    size_t pos = lcs_len;
    lcs[pos] = '\0';

    while (i > 0 && j > 0) {
        size_t idx_up = (i - 1) * (len2 + 1) + j;
        size_t idx_left = i * (len2 + 1) + (j - 1);

        if (seq1[i - 1] == seq2[j - 1]) {
            pos--;
            lcs[pos] = seq1[i - 1];
            i--;
            j--;
        } else if (dp[idx_up] >= dp[idx_left]) {
            i--;
        } else {
            j--;
        }
    }

    free(dp);
    return lcs;
}

int main(void) {
    const char *sequence1 = "AGGTAB";
    const char *sequence2 = "GXTXAYB";

    char *result = find_lcs(sequence1, sequence2);

    if (result == NULL) {
        fprintf(stderr, "Error: Failed to compute LCS\n");
        return EXIT_FAILURE;
    }

    printf("Sequence 1: %s\n", sequence1);
    printf("Sequence 2: %s\n", sequence2);
    printf("LCS: %s\n", result);
    printf("LCS Length: %zu\n", strlen(result));

    free(result);
    return EXIT_SUCCESS;
}