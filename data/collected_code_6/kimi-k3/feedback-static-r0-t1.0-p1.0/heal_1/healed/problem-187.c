#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

static bool validate_string(const char *s, size_t max_len)
{
    if (s == NULL) {
        return false;
    }
    
    size_t i;
    for (i = 0; i < max_len; i++) {
        if (s[i] == '\0') {
            return true;
        }
    }
    
    return false;
}

static size_t safe_strlen(const char *s, size_t max_len)
{
    if (s == NULL) {
        return 0;
    }
    
    size_t len = 0;
    while (len < max_len && s[len] != '\0') {
        len++;
    }
    
    return len;
}

char *find_lcs(const char *s1, const char *s2)
{
    if (s1 == NULL || s2 == NULL) {
        return NULL;
    }
    
    if (!validate_string(s1, SIZE_MAX) || !validate_string(s2, SIZE_MAX)) {
        return NULL;
    }
    
    size_t len1 = safe_strlen(s1, SIZE_MAX);
    size_t len2 = safe_strlen(s2, SIZE_MAX);
    
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
    
    size_t total_size = rows * cols;
    if (total_size > SIZE_MAX / sizeof(size_t)) {
        return NULL;
    }
    
    size_t *dp = (size_t *)calloc(total_size, sizeof(size_t));
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
    
    if (lcs_len == SIZE_MAX || lcs_len >= SIZE_MAX - 1) {
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
            if (k == 0) {
                free(dp);
                free(lcs);
                return NULL;
            }
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
    
    size_t result_len = safe_strlen(result, SIZE_MAX);
    printf("Length: %zu\n", result_len);
    
    free(result);
    return EXIT_SUCCESS;
}