#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static size_t idx3(size_t i, size_t j, size_t k, size_t d2, size_t d3)
{
    return (i * d2 + j) * d3 + k;
}

static char *find_lcs3(const char *s1, const char *s2, const char *s3)
{
    size_t len1;
    size_t len2;
    size_t len3;
    size_t d1;
    size_t d2;
    size_t d3;
    size_t total;
    size_t i;
    size_t j;
    size_t k;
    size_t pos;
    int length;
    int *dp;
    char *result;

    if (s1 == NULL || s2 == NULL || s3 == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len1 = strlen(s1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len2 = strlen(s2);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len3 = strlen(s3);
    d1 = len1 + 1U;
    d2 = len2 + 1U;
    d3 = len3 + 1U;

    if (d1 > SIZE_MAX / d2) {
        return NULL;
    }
    total = d1 * d2;
    if (total > SIZE_MAX / d3) {
        return NULL;
    }
    total *= d3;
    if (total > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    dp = calloc(total, sizeof *dp);
    if (dp == NULL) {
        return NULL;
    }

    for (i = 1U; i <= len1; i++) {
        for (j = 1U; j <= len2; j++) {
            for (k = 1U; k <= len3; k++) {
                if (s1[i - 1U] == s2[j - 1U] && s2[j - 1U] == s3[k - 1U]) {
                    dp[idx3(i, j, k, d2, d3)] =
                        dp[idx3(i - 1U, j - 1U, k - 1U, d2, d3)] + 1;
                } else {
                    int a = dp[idx3(i - 1U, j, k, d2, d3)];
                    int b = dp[idx3(i, j - 1U, k, d2, d3)];
                    int c = dp[idx3(i, j, k - 1U, d2, d3)];
                    int m = a;
                    if (b > m) {
                        m = b;
                    }
                    if (c > m) {
                        m = c;
                    }
                    dp[idx3(i, j, k, d2, d3)] = m;
                }
            }
        }
    }

    length = dp[idx3(len1, len2, len3, d2, d3)];
    result = malloc((size_t)length + 1U);
    if (result == NULL) {
        free(dp);
        return NULL;
    }

    pos = (size_t)length;
    result[pos] = '\0';
    i = len1;
    j = len2;
    k = len3;
    while (i > 0U && j > 0U && k > 0U) {
        if (s1[i - 1U] == s2[j - 1U] && s2[j - 1U] == s3[k - 1U]) {
            pos--;
            result[pos] = s1[i - 1U];
            i--;
            j--;
            k--;
        } else {
            int a = dp[idx3(i - 1U, j, k, d2, d3)];
            int b = dp[idx3(i, j - 1U, k, d2, d3)];
            int c = dp[idx3(i, j, k - 1U, d2, d3)];
            if (a >= b && a >= c) {
                i--;
            } else if (b >= c) {
                j--;
            } else {
                k--;
            }
        }
    }

    free(dp);
    return result;
}

int main(void)
{
    const char *str1 = "AGGT12";
    const char *str2 = "12TXAYB";
    const char *str3 = "12XBA";
    char *lcs;

    lcs = find_lcs3(str1, str2, str3);
    if (lcs == NULL) {
        if (fprintf(stderr, "Failed to compute LCS\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("String 1: %s\n", str1) < 0 ||
        printf("String 2: %s\n", str2) < 0 ||
        printf("String 3: %s\n", str3) < 0 ||
        printf("Longest common subsequence: %s\n", lcs) < 0 ||
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        printf("Length: %zu\n", strlen(lcs)) < 0) {
        free(lcs);
        return EXIT_FAILURE;
    }

    free(lcs);
    return EXIT_SUCCESS;
}