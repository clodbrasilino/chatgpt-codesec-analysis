#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 4096U

static char *longest_common_subsequence(const char *a, const char *b)
{
    size_t m;
    size_t n;
    size_t i;
    size_t j;
    size_t **dp;
    char *result;
    size_t len;

    if (a == NULL || b == NULL) {
        return NULL;
    }

    m = strnlen(a, MAX_INPUT_LEN);
    n = strnlen(b, MAX_INPUT_LEN);

    if (m >= MAX_INPUT_LEN || n >= MAX_INPUT_LEN) {
        return NULL;
    }

    dp = malloc((m + 1) * sizeof(size_t *));
    if (dp == NULL) {
        return NULL;
    }

    for (i = 0; i <= m; i++) {
        dp[i] = calloc(n + 1, sizeof(size_t));
        if (dp[i] == NULL) {
            for (j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return NULL;
        }
    }

    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else if (dp[i - 1][j] >= dp[i][j - 1]) {
                dp[i][j] = dp[i - 1][j];
            } else {
                dp[i][j] = dp[i][j - 1];
            }
        }
    }

    len = dp[m][n];
    result = malloc(len + 1);
    if (result == NULL) {
        for (i = 0; i <= m; i++) {
            free(dp[i]);
        }
        free(dp);
        return NULL;
    }

    result[len] = '\0';
    i = m;
    j = n;
    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) {
            len--;
            result[len] = a[i - 1];
            i--;
            j--;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    for (i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main(void)
{
    const char *seq1 = "AGGTAB";
    const char *seq2 = "GXTXAYB";
    char *lcs;

    lcs = longest_common_subsequence(seq1, seq2);
    if (lcs == NULL) {
        if (fprintf(stderr, "Failed to compute LCS\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Sequence 1: %s\n", seq1) < 0 ||
        printf("Sequence 2: %s\n", seq2) < 0 ||
        printf("LCS: %s\n", lcs) < 0 ||
        printf("Length: %zu\n", strnlen(lcs, MAX_INPUT_LEN)) < 0) {
        free(lcs);
        return EXIT_FAILURE;
    }

    free(lcs);
    return EXIT_SUCCESS;
}