#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int shortest_common_supersequence_length(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    int len1 = (int)strlen(str1);
    int len2 = (int)strlen(str2);

    int *dp = (int *)malloc((len1 + 1) * (len2 + 1) * sizeof(int));
    if (dp == NULL) {
        return -1;
    }

    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            if (i == 0) {
                dp[i * (len2 + 1) + j] = j;
            } else if (j == 0) {
                dp[i * (len2 + 1) + j] = i;
            } else if (str1[i - 1] == str2[j - 1]) {
                dp[i * (len2 + 1) + j] = dp[(i - 1) * (len2 + 1) + (j - 1)] + 1;
            } else {
                int from_left = dp[i * (len2 + 1) + (j - 1)];
                int from_above = dp[(i - 1) * (len2 + 1) + j];
                dp[i * (len2 + 1) + j] = (from_above < from_left ? from_above : from_left) + 1;
            }
        }
    }

    int result = dp[len1 * (len2 + 1) + len2];
    free(dp);
    return result;
}

int main(void) {
    const char *str1 = "AGGTAB";
    const char *str2 = "GXTXAYB";
    int result = shortest_common_supersequence_length(str1, str2);
    if (result != -1) {
        printf("%d\n", result);
    } else {
        printf("Memory allocation failed\n");
    }
    return 0;
}