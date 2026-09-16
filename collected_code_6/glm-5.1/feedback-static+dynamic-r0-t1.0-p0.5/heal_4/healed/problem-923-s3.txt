#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int shortest_common_supersequence_length(const char *str1, const char *str2) {
    size_t m = strlen(str1);
    size_t n = strlen(str2);
    
    int *dp = (int *)malloc((m + 1) * (n + 1) * sizeof(int));
    if (dp == NULL) {
        return -1;
    }
    
    for (size_t i = 0; i <= m; i++) {
        dp[i * (n + 1)] = i;
    }
    
    for (size_t j = 0; j <= n; j++) {
        dp[j] = j;
    }
    
    for (size_t i = 1; i <= m; i++) {
        for (size_t j = 1; j <= n; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i * (n + 1) + j] = dp[(i - 1) * (n + 1) + (j - 1)] + 1;
            } else {
                int top = dp[(i - 1) * (n + 1) + j];
                int left = dp[i * (n + 1) + (j - 1)];
                dp[i * (n + 1) + j] = (top < left ? top : left) + 1;
            }
        }
    }
    
    int result = dp[m * (n + 1) + n];
    free(dp);
    
    return result;
}

int main(int argc, char const * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <str1> <str2>\n", argv[0]);
        return 1;
    }
    
    int length = shortest_common_supersequence_length(argv[1], argv[2]);
    if (length < 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    printf("%d\n", length);
    return 0;
}