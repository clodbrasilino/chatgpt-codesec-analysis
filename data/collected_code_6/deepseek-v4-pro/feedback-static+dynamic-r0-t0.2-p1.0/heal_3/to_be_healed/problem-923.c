#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int shortest_common_supersequence_length(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1 = strlen(str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = strlen(str2);

    if (len1 > (size_t)(INT_MAX / (len2 + 1)) || len2 > (size_t)(INT_MAX - 1)) {
        return -1;
    }

    int *dp = (int *)malloc((len1 + 1) * (len2 + 1) * sizeof(int));
    if (dp == NULL) {
        return -1;
    }

    for (size_t i = 0; i <= len1; i++) {
        for (size_t j = 0; j <= len2; j++) {
            size_t index = i * (len2 + 1) + j;
            if (i == 0) {
                dp[index] = (int)j;
            } else if (j == 0) {
                dp[index] = (int)i;
            } else if (str1[i - 1] == str2[j - 1]) {
                dp[index] = dp[(i - 1) * (len2 + 1) + (j - 1)] + 1;
            } else {
                int from_left = dp[i * (len2 + 1) + (j - 1)];
                int from_above = dp[(i - 1) * (len2 + 1) + j];
                dp[index] = (from_above < from_left ? from_above : from_left) + 1;
            }
        }
    }

    int result = dp[len1 * (len2 + 1) + len2];
    free(dp);
    return result;
}

int main(void) {
    const char str1[] = "AGGTAB";
    const char str2[] = "GXTXAYB";
    int result = shortest_common_supersequence_length(str1, str2);
    if (result != -1) {
        printf("%d\n", result);
    } else {
        printf("Memory allocation failed\n");
    }
    return 0;
}