#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int shortest_supersequence_length(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    size_t len1 = strnlen(str1, (size_t)INT_MAX + 1UL);
    size_t len2 = strnlen(str2, (size_t)INT_MAX + 1UL);

    if (len1 > (size_t)INT_MAX || len2 > (size_t)INT_MAX) {
        return -1;
    }

    int n1 = (int)len1;
    int n2 = (int)len2;

    int **dp = (int **)calloc((size_t)(n1 + 1), sizeof(int *));
    if (dp == NULL) {
        return -1;
    }

    int i;
    for (i = 0; i <= n1; i++) {
        dp[i] = (int *)calloc((size_t)(n2 + 1), sizeof(int));
        if (dp[i] == NULL) {
            int k;
            for (k = 0; k < i; k++) {
                free(dp[k]);
            }
            free(dp);
            return -1;
        }
    }

    for (i = 0; i <= n1; i++) {
        int j;
        for (j = 0; j <= n2; j++) {
            if (i == 0) {
                dp[i][j] = j;
            } else if (j == 0) {
                dp[i][j] = i;
            } else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = (dp[i - 1][j] < dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1]) + 1;
            }
        }
    }

    int result = dp[n1][n2];

    for (i = 0; i <= n1; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main(void) {
    char *str1 = NULL;
    char *str2 = NULL;
    size_t buffer_size = 256;
    size_t len1, len2;
    int c;

    str1 = (char *)calloc(buffer_size, sizeof(char));
    if (str1 == NULL) {
        return 1;
    }

    str2 = (char *)calloc(buffer_size, sizeof(char));
    if (str2 == NULL) {
        free(str1);
        return 1;
    }

    printf("Enter first string: ");
    if (fgets(str1, (int)buffer_size, stdin) == NULL) {
        free(str1);
        free(str2);
        return 1;
    }
    len1 = strnlen(str1, buffer_size);
    if (len1 > 0 && str1[len1 - 1] == '\n') {
        str1[len1 - 1] = '\0';
        len1--;
    } else if (len1 == buffer_size - 1 && str1[len1 - 1] != '\n') {
        while ((c = getchar()) != '\n' && c != EOF) {}
    }

    printf("Enter second string: ");
    if (fgets(str2, (int)buffer_size, stdin) == NULL) {
        free(str1);
        free(str2);
        return 1;
    }
    len2 = strnlen(str2, buffer_size);
    if (len2 > 0 && str2[len2 - 1] == '\n') {
        str2[len2 - 1] = '\0';
        len2--;
    } else if (len2 == buffer_size - 1 && str2[len2 - 1] != '\n') {
        while ((c = getchar()) != '\n' && c != EOF) {}
    }

    len1 = strnlen(str1, buffer_size);
    len2 = strnlen(str2, buffer_size);

    if (len1 >= buffer_size || len2 >= buffer_size) {
        free(str1);
        free(str2);
        return 1;
    }

    int length = shortest_supersequence_length(str1, str2);
    if (length == -1) {
        printf("Error computing shortest common supersequence.\n");
        free(str1);
        free(str2);
        return 1;
    }

    printf("Length of shortest common supersequence: %d\n", length);

    free(str1);
    free(str2);

    return 0;
}